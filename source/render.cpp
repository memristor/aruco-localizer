#include <string>
#include <sstream>
#include <filesystem>

#include <opencv2/opencv.hpp>
#include <eigen3/Eigen/Dense>

namespace render {

    cv::Point project2d(Eigen::Vector3cd point, double var1 = 0, double var2 = 0, bool orth = 0) {

        Eigen::Vector3cd camera_point(3, 3, 5);
        Eigen::Vector3cd camera_direction(1, 1 + var2, 1);
        // Eigen::Vector3cd camera_direction(-2.45322, -2.08319, -2+var1);

        Eigen::Vector3cd screen_origin = camera_point + camera_direction;

        Eigen::Vector3cd projection_ray;

        if (orth)
            projection_ray = camera_direction;
        else
            projection_ray = point - camera_point;


        Eigen::Vector3cd projection_point = 
            point + ((screen_origin - point).dot(camera_direction) / projection_ray.dot(camera_direction)) * projection_ray;
          
        Eigen::Vector3cd screen_z = camera_direction / camera_direction.norm();

        Eigen::Vector3cd screen_y_intersect =
            ((screen_origin).dot(camera_direction) / camera_direction.dot(camera_direction)) * camera_direction;

        Eigen::Vector3cd screen_y = (screen_y_intersect - screen_origin) / (screen_y_intersect - screen_origin).norm();
        Eigen::Vector3cd screen_x = screen_y.cross(screen_z) / screen_y.cross(screen_z).norm();

        Eigen::Matrix3cd M1;
        M1.row(0) = screen_x;
        M1.row(1) = screen_y;
        M1.row(2) = screen_z;

        Eigen::Vector3cd screen_point = M1 * (projection_point);

        Eigen::Vector3cd projection_xy = projection_point - screen_origin;

        Eigen::Vector3cd projection_line_x =
            camera_direction.cross(Eigen::Vector3cd(0,0,1)) / camera_direction.cross(Eigen::Vector3cd(0,0,1)).norm();

        Eigen::Vector3cd projection_line_y =
            camera_direction.cross(projection_line_x) / camera_direction.cross(projection_line_x).norm();

        Eigen::Vector3cd projection_point_x = 
            projection_line_x.dot(projection_xy) / projection_line_x.dot(projection_line_x) * projection_line_x;

        Eigen::Vector3cd projection_point_y = 
            projection_line_y.dot(projection_xy) / projection_line_y.dot(projection_line_y) * projection_line_y;

        double dist_x = projection_point_x.norm() * std::pow(-1, (projection_point_x[0].real() / projection_line_x[0].real() > 0));
        double dist_y = projection_point_y.norm() * std::pow(-1, (projection_point_y[0].real() / projection_line_y[0].real() > 0));

        // std::cout << dist_x << " - " << dist_y << std::endl;

        return cv::Point(dist_x * 30, dist_y * 30);

    }

    void render() {

        double var1 = 0, var2 = 0;
        bool proj = 1;

        char key;
        while (key != 27) {

            cv::Point center = cv::Point(400, 300);

            // Eigen::Vector3cd i(2, 2, -1.52);
            // Eigen::Vector3cd j(-2.27, -2.27, 0);
            // Eigen::Vector3cd k(1.07, 1.07, 2.83);

            Eigen::Vector3cd i(-1, 0, 0);
            Eigen::Vector3cd j(0, -1, 0);
            Eigen::Vector3cd k(0, 0, -1);

            Eigen::Vector3cd o(0, 0, 0);

            // Eigen::Vector3cd A(-1, -1, 6.51717);

            Eigen::Vector3cd A(1 + var1, 1 + 2 * var1, 1);

            Eigen::Vector3cd cube[] = {
                A,              // A
                A + i,          // B
                A + j,          // D
                A + i + j,      // C
                A + k,          // E
                A + i + k,      // F
                A + j + k,      // H
                A + i + j + k   // G
            };

            for (auto& point : cube) {
                point *= 1;
            }

            cv::Point cube2d[8];

            for (auto i = 0; i < 8; ++i) {
                // std::cout << i << "........" << std::endl;
                cube2d[i] = project2d(cube[i], var1, var2, proj) * 1 + center;
            }

            // if (key != -1)
            // std::cout << "########" << std::endl;
            // std::cout << project2d(cube[0]) << std::endl;

            cv::Mat plane(600, 800, CV_8UC3, cv::Scalar(0,0,0));

            for (auto& point : cube2d) {
                cv::circle(plane, point, 0, cv::Scalar(255,255,255), 4);
            }

            // std::cout << std::endl;

            cv::putText(plane, "X", project2d(i * 10, var1, var2, proj) + center, 1, 2, cv::Scalar(100,100,255), 2);
            cv::putText(plane, "Y", project2d(j * 10, var1, var2, proj) + center, 1, 2, cv::Scalar(100,255,100), 2);
            cv::putText(plane, "Z", project2d(k * 10, var1, var2, proj) + center, 1, 2, cv::Scalar(255,100,100), 2);

            cv::arrowedLine(plane, project2d(o, var1, var2, proj) + center, project2d(i * 10, var1, var2, proj) + center, cv::Scalar(0,0,255), 1);
            cv::arrowedLine(plane, project2d(o, var1, var2, proj) + center, project2d(j * 10, var1, var2, proj) + center, cv::Scalar(0,255,0), 1);
            cv::arrowedLine(plane, project2d(o, var1, var2, proj) + center, project2d(k * 10, var1, var2, proj) + center, cv::Scalar(255,0,0), 1);
            
            std::vector<cv::Point> poly; 
            poly.push_back(cube2d[0]);
            poly.push_back(cube2d[2]);
            poly.push_back(cube2d[3]);
            poly.push_back(cube2d[1]);

            cv::fillConvexPoly(plane, poly, cv::Scalar(100,100,100));

            cv::line(plane, cube2d[0], cube2d[1], cv::Scalar(180,180,180), 1);
            cv::line(plane, cube2d[0], cube2d[2], cv::Scalar(180,180,180), 1);
            cv::line(plane, cube2d[2], cube2d[3], cv::Scalar(180,180,180), 1);
            cv::line(plane, cube2d[3], cube2d[1], cv::Scalar(180,180,180), 1);

            cv::line(plane, cube2d[4], cube2d[5], cv::Scalar(180,180,180), 1);
            cv::line(plane, cube2d[4], cube2d[6], cv::Scalar(180,180,180), 1);
            cv::line(plane, cube2d[6], cube2d[7], cv::Scalar(180,180,180), 1);
            cv::line(plane, cube2d[7], cube2d[5], cv::Scalar(180,180,180), 1);

            cv::line(plane, cube2d[0], cube2d[4], cv::Scalar(180,180,180), 1);
            cv::line(plane, cube2d[1], cube2d[5], cv::Scalar(180,180,180), 1);
            cv::line(plane, cube2d[2], cube2d[6], cv::Scalar(180,180,180), 1);
            cv::line(plane, cube2d[3], cube2d[7], cv::Scalar(180,180,180), 1);

            cv::imshow("Display", plane);
            key = (char) cv::waitKey(1);

            // if (key != -1)
            //     std::cout << (int) key << std::endl;

            if(key == 83)
                var1 -= 0.1;

            if(key == 81)
                var1 += 0.1;

            if(key == 84)
                var2 -= 0.1;

            if(key == 82)
                var2 += 0.1;

            if(key == 82)
                var2 += 0.1;

            if(key == 112) {
                proj = !proj;
                var1 = 0;
                var2 = 0;
            }

        }

        

    }

}
