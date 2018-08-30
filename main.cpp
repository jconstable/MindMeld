#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <windows.h>

#include <iostream>
#include <process.h>



#include "Util\Macros.h"
#include "Application\HelloTriangleApplication.h"

#define ALLOW_VULKAN_RENDERDOC_CAPTURE 0

#if ALLOW_VULKAN_RENDERDOC_CAPTURE
#include "../renderdoc/renderdoc_app.h"
RENDERDOC_API_1_1_2 *rdoc_api = NULL;
#endif

typedef struct
{
	LPSTR lpEnvAddress;
	LPSTR lpCmdLine;
	LPSTR lpCmdShow;
	DWORD dwReserved;
} LOADPARMS32;

int main() {
	HelloTriangle::HelloTriangleApplication app;
	RUN_WITH_TRY(app.initWindow();)
	RUN_WITH_TRY(app.initGraphics();)


	HelloTriangle::Level::Level* level = new HelloTriangle::Level::Level();
	app.setLevel(level);

#if ALLOW_VULKAN_RENDERDOC_CAPTURE
	LPCSTR dllPath = (LPCSTR) "C:\\Users\\jcons\\src\\VulkanIntro\\renderdoc\\renderdoc.dll";
	HMODULE hMyDLL = GetModuleHandle(dllPath);
	if (hMyDLL == nullptr)
	{
		hMyDLL = LoadLibrary(dllPath);
	}

	if (hMyDLL != nullptr)
	{
		pRENDERDOC_GetAPI RENDERDOC_GetAPI = (pRENDERDOC_GetAPI)GetProcAddress(hMyDLL, "RENDERDOC_GetAPI");
		int ret = RENDERDOC_GetAPI(eRENDERDOC_API_Version_1_1_2, (void **)&rdoc_api);
		assert(ret == 1);

		//rdoc_api->StartFrameCapture()
		//RENDERDOC_InputButton buttons[] = { RENDERDOC_InputButton::eRENDERDOC_Key_0 };
		//rdoc_api->SetCaptureKeys(buttons, 1);

		rdoc_api->StartFrameCapture(NULL, NULL);
	}
#endif

	int exitCode = app.mainLoop();
	
	app.setLevel(nullptr);
	level->cleanup();
	delete(level);

	RUN_WITH_TRY(app.cleanup();)

#if ALLOW_VULKAN_CAPTURE
#endif

	//system("pause");

	return exitCode;
}