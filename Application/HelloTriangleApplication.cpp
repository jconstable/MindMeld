#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>

#include <ctime>
#include <chrono>
#include <thread>

#include "HelloTriangleApplication.h"
#include "../Util/Macros.h"
#include "../Engine/EngineInfo.h"
#include "AppInfo.h"

#define FRAME_RATE 60

void errorCallback(int error, const char* desc)
{
	std::cout << "Error creating window! (" << error << ") " << desc << std::endl;
	throw std::runtime_error(desc);
}

const int WIDTH = 800;
const int HEIGHT = 600;

namespace HelloTriangle {
	HelloTriangleApplication::HelloTriangleApplication() :
		m_window(nullptr),
		m_instance(),
		m_wrapper()
	{
	}

	void HelloTriangleApplication::initGraphics()
	{
		MindMeld::ApplicationInfo appInfo;
		appInfo.appName = APP_NAME;
		appInfo.majorVersion = APP_VERSION_MAJOR;
		appInfo.minorVersion = APP_VERSION_MINOR;
		appInfo.microVersion = APP_VERSION_MICRO;
		appInfo.windowWidth = WIDTH;
		appInfo.windowHeight = HEIGHT;
		m_wrapper.createInstance(m_instance, m_window, appInfo);
	}

	void HelloTriangleApplication::initWindow()
	{
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		glfwSetErrorCallback(errorCallback);
		m_window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan Window", nullptr, nullptr);
	}

	const uint64_t numerator = (1LL << 32) / 10000;
	inline long getFrameTimeMS(std::chrono::system_clock::time_point &startTime, std::chrono::system_clock::time_point &endTime)
	{
		auto delta = (endTime - startTime).count();

		return (delta * numerator) >> 32;
	}

	float getTargetFrameTimeMS()
	{
		return 1000.0f / static_cast<float>(FRAME_RATE);
	}

	int HelloTriangleApplication::mainLoop()
	{
		bool shouldExit = false;
		int code = EXIT_FAILURE;
		float targetFrameTime = getTargetFrameTimeMS();

		std::chrono::system_clock::time_point startTime;
		std::chrono::system_clock::time_point endTime;

		while (!shouldExit)
		{
			startTime = std::chrono::system_clock::now();

#ifdef DEBUG
			try {
#endif
				if (glfwWindowShouldClose(m_window))
				{
					code = EXIT_SUCCESS;
					shouldExit = true;
				}

				glfwPollEvents();

				if (m_currentLevel != nullptr)
				{
					m_wrapper.drawEntities(m_currentLevel->getEntites());
				}
#ifdef DEBUG
			}catch(const std::exception& e)
			{
				std::cout << "Application received unhandled exception: " << e.what() << std::endl;
				shouldExit = true;
			}
#endif
			
			endTime = std::chrono::system_clock::now();

			unsigned long frameTime = getFrameTimeMS(startTime, endTime);
			long delta = (long)(targetFrameTime - (float)frameTime);


			if (delta > 0.0f)
			{
				//std::this_thread::sleep_for(std::chrono::milliseconds(delta));
			}
				
		}

		return EXIT_FAILURE;
	}

	void HelloTriangleApplication::setLevel(Level::Level* level)
	{
		if( m_currentLevel != nullptr)
		{
			m_wrapper.cleanupEntities(m_currentLevel->getEntites());
		}

		m_currentLevel = level;
	}

	void HelloTriangleApplication::cleanup()
	{
		m_wrapper.cleanup();

		glfwDestroyWindow(m_window);

		glfwTerminate();
	}
}