/*
    * 作者（B站UP主，感谢三连！！！）：FaithBook-_-
    * GitHub：faithbook233
    * 技术交流群（非粉丝群）：815093873
    *
    *
    * 本项目是我学习C++与渲染算法的一个小Demo，代码开源供广大网友学习
    * 有问题尽量自己解决，知识不够先问度娘，加油少年！
    *
    * 运行环境：Windows 10 Visual Studio 2019
    * 代码参考《Ray Tracing in One Weekend》
    * 文献中并未提及运行环境等信息，我见到有人用Visual Studio Code实现了，但我更热衷于用VS，所以决定用Visual Studio实现代码
    * 文献中代码为偏C风格，我将代码改为纯C++代码，并对算法和代码命名风格进行了升级与整理
    * 原文为单精度浮点，我整体改为双精度浮点了
    *
    * 运行此项目必须的步骤：
    *       ①准备Visual Studio 2019或更高的版本，低版本可能有兼容问题
    *       ②（已实现）在项目属性->调试->命令行调试中输入 >data.ppm  可以将控制台程序输出到data.ppm
    *       ③用ppm viewer打开data.ppm即可看到效果
    *
    * 压缩包包含文件：
    *       ①项目所需文件
    *       ②ppm viewer（ppm图片查看器）
    *
    * 参考文献《Ray Tracing in One Weekend》 Peter Shirley Version 1.54 Copyright 2018. Peter Shirley. All rights reserved

*/


/*
    **预期功能：
    * 具有材质、金属、贴图、实体的渲染方法
    * 光线追踪等基础算法
    * 渲染时查看（通过第三方库实时展示图片）

*/

#include <iostream>
#include <string>
#include <sstream>
#include"Sphere.h"
#include"HitableList.h"
#include"Camera.h"
#include "Random.h"
#include"Material.h"
#include"Hitable.h"
using namespace std;

#include <opencv.hpp>
#include <highgui.hpp>
using namespace cv;

Vec3 Color(const Ray& R, Hitable* World, int Depth)
{
    HitRecord Rec;
    if (World->Hit(R, 0.001, DBL_MAX, Rec))
    {
        Ray Scattered;
        Vec3 Attenuation;
        if (Depth < 50 && Rec.MatPtr->Scatter(R, Rec, Attenuation, Scattered))
        {
            return Attenuation * Color(Scattered, World, Depth + 1);
        }
        else
        {
            return Vec3(0, 0, 0);
        }
    }
    else
    {
        Vec3 UnitDirection = UnitVector(R.Direction());
        double T = 0.5 * (UnitDirection.Y() + 1.0);
        return (1.0 - T) * Vec3(1.0, 1.0, 1.0) + T * Vec3(0.5, 0.7, 1.0);
    }
}

/*
    随机产生场景实体
*/
Hitable* RandomScene()
{
    int N = 500;
    Hitable** List = new Hitable * [N + 1];
    //生成地面（一个很大的球体）
    List[0] = new Sphere(Vec3(0, -1000, 0), 1000, new Lambertian(Vec3(0.5, 0.5, 0.5)));
    int i = 1;
    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            double ChooseMat = RandDbl();
            Vec3 Center(a + 0.9 * RandDbl(), 0.2, b + 0.9 * RandDbl());
            if ((Center - Vec3(4, 0.2, 0)).Vec3Length() > 0.9)
            {
                if (ChooseMat < 0.8)
                {
                    List[i++] = new Sphere(
                        Center, 0.2,
                        new Lambertian(Vec3(
                            RandDbl() * RandDbl(),
                            RandDbl() * RandDbl(),
                            RandDbl() * RandDbl()))
                    );
                }
                else if (ChooseMat < 0.95)
                {
                    List[i++] = new Sphere(
                        Center, 0.2,
                        new Metal(Vec3(
                            0.5 * (1 + RandDbl()),
                            0.5 * (1 + RandDbl()),
                            0.5 * (1 + RandDbl())),
                            0.5 * RandDbl())
                    );
                }
                else
                {
                    List[i++] = new Sphere(Center, 0.2, new Dielectric(1.5));
                }
            }
        }
    }
    List[i++] = new Sphere(Vec3(0, 1, 0), 1.0, new Dielectric(1.5));
    List[i++] = new Sphere(Vec3(-4, 1, 0), 1.0, new Lambertian(Vec3(0.4, 0.2, 0.1)));
    List[i++] = new Sphere(Vec3(4, 1, 0), 1.0, new Metal(Vec3(0.7, 0.6, 0.5), 0.0));
    return new HitableList(List, i);
}



int main()
{
    //视野像素
    int nx;
    int ny;
    int ns;
    bool bRenderDisplay = true;

    int RenderMode = 3;
    switch(RenderMode)
    {
    case 1:
        nx = 200;
		ny = 100;
        ns = 10;                 
        break;
    case 2:  
		nx = 1000;
		ny = 500;
		ns = 1;
        break;
    case 3: 
		nx = 1000;
		ny = 500;
		ns = 10;
        break; 
    default: return -1;
    }
    //每个像素检测的次数，次数越多越真实，计算量越大，渲染越慢
    
   
    srand((int)time(NULL));
    std::cout << "P3\n" << nx << " " << ny << "\n255\n"; //信息头
    /*
        初始化相机
    */
    Vec3 LookFrom(13, 2, 3);
    Vec3 LookAt(0, 0, 0);
    double DistToFocus = (LookFrom - LookAt).Vec3Length();//=10;
    double Aperture = 0.1;
    Camera Cam(LookFrom, LookAt, Vec3(0, 1, 0), 20, double(nx) / double(ny), Aperture, DistToFocus);

    /*
        初始化世界
    */
    Hitable* World = RandomScene();

    //渲染
    int WindowWidth;
    int WindowHeight;
    if (nx > ny)  //横版图片
    {
		WindowHeight = 1080 - 200;
		WindowWidth = (int)((double)WindowHeight * (double)nx / (double)ny);
    }
    else
    {
		WindowWidth = 1920 - 200;
		WindowHeight = (int)((double)WindowWidth * (double)ny / (double)nx);
		
    }
    Mat lena(ny, nx, CV_8UC3, Scalar(50, 50, 50));
	namedWindow("图像预览（渲染中）", WINDOW_NORMAL);
    moveWindow("图像预览（渲染中）", (int)((1920.0 - WindowWidth) / 2), (int)((1080.0 - WindowHeight) / 2)-50);
    resizeWindow("图像预览（渲染中）",  WindowWidth, WindowHeight);
    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            Vec3 Col(0, 0, 0);
            for (int s = 0; s < ns; s++)
            {
                //UV为相对屏幕的位置占比

                double U = double(i + Rand01()) / double(nx);
                double V = double(j + Rand01()) / double(ny);
                Ray R = Cam.GetRay(U, V);
                Vec3 P = R.PointAtParameter(2.0);

                /*
                重大错误
                */
                Col += Color(R, World, 0);
            }
            Col /= double(ns);
            Col = Vec3(sqrt(Col[0]), sqrt(Col[1]), sqrt(Col[2]));
            //将0-1值映射到0-255用于最终输出，因为PPM颜色信息值为0-255
            int ir = int(255.99 * Col[0]);
            int ig = int(255.99 * Col[1]);
            int ib = int(255.99 * Col[2]);

            if (bRenderDisplay)
            {
				lena.at<cv::Vec3b>(ny - 1-j, i)[0] = ib;
				lena.at<cv::Vec3b>(ny - 1-j, i)[1] = ig;
				lena.at<cv::Vec3b>(ny - 1-j, i)[2] = ir;
            }
            std::cout << ir << "  " << ig << "  " << ib << std::endl;
            //像素更新
          /*  if (bRenderDisplay)
			{
				imshow("图像预览（渲染中）", lena);
				waitKey(1);
			}*/
        }
        //行更新
		if (bRenderDisplay)
		{
			imshow("图像预览（渲染中）", lena);
			waitKey(1);
		}
    }
    //渲染完成，将图片保存为其他格式
    waitKey(0);
	destroyAllWindows();

    return 0;
}

