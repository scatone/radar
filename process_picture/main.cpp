#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <filesystem> // C++17
#include <sys/stat.h>  
#include <sys/types.h>  
using namespace std;

void work1(std::string inputDir, std::string outputDir)
{
    std::string staticoutputDir = outputDir;
    int width = 640; // 裁剪宽度
    int height = 384; // 裁剪高度
    int x = 320; // 裁剪x坐标
    int y = 384; // 裁剪y坐标
    int cnt = 0;
    int index = 0;
    // 遍历目录中的所有图片文件
    cv::Mat image;
    std::vector<std::string> files;
    cv::glob(inputDir + "/*", files); // 假设我们处理jpg图片
    cout << files.size() << endl;
    for (const auto& file : files) {
        cout << outputDir << endl;
        // 读取图片
        //cout << file << endl;
        image = cv::imread(file);
        if(image.cols == 640 && image.rows == 384)
        {
            x = 0;
            y = 0;
        }
        else if (image.cols == 1080 && image.rows == 720)
        {
            x = 220;
            y = 168;
        }
        else if (image.cols == 1280 && image.rows == 720)
        {
            x = 320;
            y = 168;
        }
        else//1280 x 1024
        {
            x = 320; // 裁剪x坐标
            y = 384; // 裁剪y坐标
        }
        
        if (image.empty()) {
            std::cerr << "Error: Image " << file << " cannot be loaded." << std::endl;
            continue;
        }

        // 获取文件名
        std::filesystem::path p(file);
        std::string filename = p.filename().string();
        // 裁剪图片
        cv::Rect rect(x, y, width, height);
        cv::Mat croppedImage = image(rect);
        // 保存裁剪后的图片
        std::string outputFile = outputDir + "/" + filename;
        cv::imwrite(outputFile, croppedImage);
        cout << filename << endl;
        cnt += 1;
        if (cnt > 50)
        {
            cout << endl;
            cnt %= 50;
            index += 1;
            outputDir = staticoutputDir + to_string(index);
            const char* c_str_ptr = outputDir.c_str(); 
            mkdir(c_str_ptr, 0755);
        }
    }

}

void work2(std::string inputDir, std::string outputDir)
{
    std::string staticoutputDir = outputDir;
    // 遍历目录中的所有图片文件
    cv::Mat image;
    std::vector<std::string> files;
    cv::glob(inputDir + "/*", files); // 假设我们处理jpg图片
    int cnt = 51;
    int index = 0;
    for (const auto& file : files) {
        if (cnt > 50)
        {
            cnt %= 50;
            index += 1;
            outputDir = staticoutputDir + to_string(index);
            const char* c_str_ptr = outputDir.c_str(); 
            mkdir(c_str_ptr, 0755);
        }
        // 读取图片
        image = cv::imread(file);
        // 计算新的宽度和高度，同时保持宽高比
        cv::Size dstSize(640, 384);         
        cv::Mat dst;
        cv::resize(image, dst, dstSize, 0, 0, cv::INTER_LINEAR);  
        // 获取文件名
        std::filesystem::path p(file);
        std::string filename = p.filename().string();
        // 保存裁剪后的图片
        std::string outputFile = outputDir + "/" + filename;
        cv::imwrite(outputFile, dst);
        cnt += 1;
    }

}

void test()
{
    cv::Mat src = cv::imread("/home/zhouyan/下载/test_image/wind72.jpg");
    cv::Size dstSize(640, 384);  
  
    // 创建目标图像矩阵  
    cv::Mat dst;  
  
    // 使用resize函数调整图片大小  
    cv::resize(src, dst, dstSize, 0, 0, cv::INTER_LINEAR);  
    // 保存或展示缩放后的图像
    cv::imwrite("/home/zhouyan/下载/test_image/wind72_out.jpg", dst);
}

int main() {
    std::string inputDir = "/home/zhouyan/下载/images"; // 输入图片目录
    std::string outputDir = "/home/zhouyan/下载/outs/out_images"; // 输出图片目录
    std::string outputDir1 = "/home/zhouyan/下载/out/out_images"; // 输出图片目录
    // work1(inputDir, outputDir);
    work2(inputDir, outputDir1);
    // test();
    return 0;
}
