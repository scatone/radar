#include <core/session/onnxruntime_cxx_api.h>
#include <core/providers/cuda/cuda_provider_factory.h>
#include <core/session/onnxruntime_c_api.h>
#include <core/providers/tensorrt/tensorrt_provider_factory.h>

#include <opencv2/opencv.hpp>
#include <sophus/se3.h>

#include <iostream>

Sophus::SE3 computePoseDNN(Mat img_1, Mat img_2, Ort::Session &session, Ort::MemoryInfo &memory_info);

//输入网络的维度
static constexpr const int width = 512;
static constexpr const int height = 512;
static constexpr const int channel = 3;
std::array<int64_t, 4> input_shape_{ 1,height, width,channel};

using namespace cv;
using namespace std;
int main()
{
	//模型位置
    string model_path = "../model.onnx";

    Ort::Env env(OrtLoggingLevel::ORT_LOGGING_LEVEL_WARNING, "PoseEstimate");
    Ort::SessionOptions session_options;
    //CUDA加速开启
    OrtSessionOptionsAppendExecutionProvider_Tensorrt(session_options, 0); //tensorRT
    OrtSessionOptionsAppendExecutionProvider_CUDA(session_options, 0);
    session_options.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_ALL);
    Ort::AllocatorWithDefaultOptions allocator;
    //加载ONNX模型
    Ort::Session session(env, model_path.c_str(), session_options);
    Ort::MemoryInfo memory_info = Ort::MemoryInfo::CreateCpu(OrtAllocatorType::OrtArenaAllocator, OrtMemType::OrtMemTypeDefault);
    //打印模型的信息
    printModelInfo(session,allocator);

	Mat img_1 = imread("/path_to_your_img1",IMREAD_COLOR);
    Mat img_2 = imread("/path_to_your_img2",IMREAD_COLOR);
    Sophus::SE3 pose = computePoseDNN(img_1,img_2,session,memory_info);
    
}
————————————————

                            版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。
                        
原文链接：https://blog.csdn.net/qq_42995327/article/details/122622222