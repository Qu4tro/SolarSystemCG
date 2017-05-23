#include "SetMaterial.h"

SetMaterial::SetMaterial(float s){
    shininess = s;

    isDiffuse = true;
    float default_d[] = {0.8, 0.8, 0.8, 1};
    float default_s[] = {0,     0,   0, 1};
    float default_e[] = {0,     0,   0, 1};

    std::copy(default_d, default_d + 4, diff_or_amb);
    std::copy(default_s, default_s + 4, specular);
    std::copy(default_e, default_e + 4, emissive);
}

void SetMaterial::setDiffuse(fTriple t){
    float tmp[] = {t.x, t.y, t.z, 1};
    std::copy(tmp, tmp + 4, diff_or_amb);
    isDiffuse = true;
}
void SetMaterial::setAmbient(fTriple t){
    float tmp[] = {t.x, t.y, t.z, 1};
    std::copy(tmp, tmp + 4, diff_or_amb);
    isDiffuse = false;
}
void SetMaterial::setSpecular(fTriple t){
    float tmp[] = {t.x, t.y, t.z, 1};
    std::copy(tmp, tmp + 4, specular);
}
void SetMaterial::setEmissive(fTriple t){
    float tmp[] = {t.x, t.y, t.z, 1};
    std::copy(tmp, tmp + 4, emissive);
}

void SetMaterial::apply() {
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	
    if (isDiffuse){
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_or_amb);
    } else {
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, diff_or_amb);
    }
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissive);
}
