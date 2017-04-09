#include "camera.h"

camera::camera(vector<element> elements, vector<light> lights)
{
    this->elements = elements;
    this->lights = lights;
    this->refreshParameter();
}

void camera::click(){

    cv::Mat imageMat = cv::Mat(res_y, res_x, CV_8UC3);

   transformElements();

    raytracer rt = raytracer(this->elements, this->lights);
    ray r = {pos, vector4 {0,0,0,0}};

    for(int j = 0; j < res_y; j++)
        for(int i = 0; i < res_x; i++){
            r.origin = Pij(i,j);
            vector4 dir = (r.origin*(-1)); dir.normalize();
            r.dir = dir;
            vector4 color = rt.trace(r, depth);
            cv::Vec3b &pixelVal = imageMat.at<cv::Vec3b>(j,i);
            pixelVal[0] = color.z;
            pixelVal[1] = color.y;
            pixelVal[2] = color.x;
        }

    vector<int> compression_params;
        compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
        compression_params.push_back(9);

        try {
            imwrite("flucktracer.png", imageMat, compression_params);
        }
        catch (runtime_error& ex) {
            fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
        }
}



void camera::setPosition(vector4 pos){
    this->pos = pos;
    this->refreshParameter();

}

void camera::setPOI(vector4 poi){
    this->poi = poi;
    this->refreshParameter();
}

void camera::refreshParameter(){
    this->n = pos - poi; this->n.normalize();
    this->u = cross_prod(up,this->n); u.normalize();
    this->v = cross_prod(n,u); v.normalize();
}

void camera::transformElements(){
    matrix4 world2camera = {{n.x,u.x,v.x,0},
                            {n.y,u.y,v.y,0},
                            {n.z,u.z,v.z,0},
                            {0  ,0  ,0  ,1}};
    world2camera = world2camera * matrix4 {{1     ,0     ,0     ,0},
                                           {0     ,1     ,0     ,0},
                                           {0     ,0     ,1     ,0},
                                           {-pos.x,-pos.y,-pos.z,1}};

    for(unsigned int i = 0; i < elements.size(); i++){
        elements.at(i).to_camera_base(world2camera * elements.at(i).base);
    }
    for(unsigned int i = 0; i < lights.size(); i++){
        lights.at(i).to_camera_base(world2camera);
    }
}
