#include "vec3.hpp"
#include "ray.hpp"
#include "shape.hpp"
#include <fstream>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

vector<Sphere> spheres = {
        Sphere(Vec3(1, 0, -5), 0.5),
        Sphere(Vec3(-1, 0, -3), 0.5),
        Sphere(Vec3(0, 0, -5), 0.5),
};

Vec3 origin(0, 0, 0);
Vec3 lower_left_corner(-2, -1, -1);
Vec3 horizontal(4, 0, 0);
Vec3 vertical(0, 2, 0);

struct Light{
    Vec3 source;
    Vec3 intensity;
    Light(float x,float y,float z,float r,float g,float b) : source(x, y, z), intensity(r, g, b){
    }
};
vector<Light> lights = {
    // Light(1, 1, 0, 0, 1, 0),
    Light(-1, 1, 0, 1, 0, 0)
};

Vec3 color(const Ray& r){

    for(auto &s : spheres){

        float t =  s.intersect(r);

        // sphere
        if (t > 0.0) {

            // shading
            // Normal
            Vec3 N = unit_vector(r.point_at_parameter(t) - s.getCenter());
            Vec3 color(0, 0, 0);
            for(auto &l : lights){
                Vec3 L = unit_vector(l.source - r.point_at_parameter(t));
                float lightness = max(0.0f, dot(N, L));

                color += lightness * l.intensity;
            }

            color.e[0] = min(1.0f, color.r());
            color.e[1] = min(1.0f, color.g());
            color.e[2] = min(1.0f, color.b());

            return color;
        }

    }
    // background
    Vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0-t)* Vec3(1, 1, 1) + t* Vec3(0.5, 0.7, 1.0);
}
int main(int argc, char *argv[]) {
    int width = 2000;
    int height = 1000;

    ofstream file;
    file.open("out/ray.ppm");
    // 
    //
    file << "P3\n" << width << " " << height << "\n255\n";

    for(int j = height-1; j >= 0; j--){
        for(int i = 0; i < width; i++){
            float u = float(i) / float(width);
            float v = float(j) / float(height);
            Vec3 uvcenter = lower_left_corner + u * horizontal + v * vertical;
            Ray r(origin, unit_vector(uvcenter - origin));
            Vec3 c = color(r);

            file << int(c.r() * 255) << " " << int(c.g() * 255) << " " << int(c.b() * 255) << "\n";

        }
    }

    cout << "Image has been save to ./out/ray.ppm" << endl;
    return 0;
}
