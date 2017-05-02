#include "Bezier.h"

std::vector<std::string> split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
    }
    return elems;
}

Bezier::Bezier(std::string bezier_file){

    std::ifstream ifile(bezier_file);
    std::string line;
    std::vector<std::string> lineVector;

    std::vector<fTriple> points;

    std::getline(ifile, line);
    int nPatches = stoi(line);

    std::vector<std::vector<int>> indices(nPatches);
    for(int i = 0; i < nPatches; i++){
        std::getline(ifile, line); 
        for(auto index: split(line, ',')){
            indices[i].push_back(stoi(index));
        }
    }

    std::getline(ifile, line); 
    int nCtrlPoints = stoi(line);
    while (std::getline(ifile, line)) {
        lineVector = split(line, ',');
        points.push_back(fTriple(stof(lineVector[0]),
                    stof(lineVector[1]),
                    stof(lineVector[2])
                    ));
    }
    assert(points.size() == nCtrlPoints);

    for(int i = 0; i < nPatches; i++){
        patches.push_back(Bezier(points, indices[i]));
    }
}

Bezier::Bezier(std::vector<fTriple> points, std::vector<int> indices){
    for(int i: indices){
        controlPoints.push_back(points[i]);
    }
}

Bezier::Bezier(std::vector<fTriple> ctrlPoints){
    controlPoints = ctrlPoints;

}

float B(int x, float u){
    switch(x){
        case 0:
            return (1 - u) * (1 - u) * (1 - u);
        case 1:
            return 3 * u * (1 - u) * (1 - u);
        case 2:
            return 3 * u * u * (1 - u);
        case 3:
            return u * u * u;
        default:
            exit(1);
    }
}

fTriple bezierCurve(float t, fTriple C0, fTriple C1, fTriple C2, fTriple C3){

    /* std::cout << C0.toLine(); */
    /* std::cout << t << std::endl; */
    C0.vector_scale(B(0, t));
    /* std::cout << C0.toLine(); */
    C1.vector_scale(B(1, t));
    C2.vector_scale(B(2, t));
    C3.vector_scale(B(3, t));

    C0.incr(C1);
    C0.incr(C2);
    C0.incr(C3);
  
    std::cout <<  C0.x <<  "  |  "  << C0.y  << " | " << C0.z << std::endl;
    return fTriple(C0.x, C0.y, C0.z);
}

fTriple Bezier::bezierSurface(float s, float t){
    return bezierCurve(t, bezierCurve(s, controlPoints[0],  controlPoints[1],  controlPoints[2],  controlPoints[3]),
                          bezierCurve(s, controlPoints[4],  controlPoints[5],  controlPoints[6],  controlPoints[7]),
                          bezierCurve(s, controlPoints[8],  controlPoints[9],  controlPoints[10], controlPoints[11]),
                          bezierCurve(s, controlPoints[12], controlPoints[13], controlPoints[14], controlPoints[15]));
}

std::vector<fTriple> Bezier::getPoints(){
    std::vector<fTriple> points;

    if (controlPoints.size() <= 0){
        for(auto b: patches){
            auto bp = b.getPoints();
            points.insert(points.end(), bp.begin(), bp.end());
        }
    } else {
        assert(controlPoints.size() == BEZIER_N_VERTICES);
        int depth = 10;

        float step = 1.0f / (float) depth;
        float u, v, u2, v2;
        for (int i = 0; i < depth; i++) {
            for (int j = 0; j < depth; j++) {
                u = i*step;
                v = j*step;
                u2 = (i + 1)*step;
                v2 = (j + 1)*step;

                fTriple p0 = bezierSurface(u, v);
                fTriple p1 = bezierSurface(u, v2);
                fTriple p2 = bezierSurface(u2, v);
                fTriple p3 = bezierSurface(u2, v2);

                /* std::cout << u << " " << v << std::endl; */
                /* std::cout << p0.toLine(); */
                /* std::cout << p1.toLine(); */
                /* std::cout << p2.toLine(); */
                /* std::cout << p3.toLine(); */

                points.push_back(p0);
                points.push_back(p2);
                points.push_back(p3);

                points.push_back(p0);
                points.push_back(p3);
                points.push_back(p1);

            }
        }
    }

    return points;
}

