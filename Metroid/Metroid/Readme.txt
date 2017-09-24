-------------------------------INTRODUCE--------------------------------------------
This is Metroid replica project (Included basic C++ DirectX9 game framework)

-------------------------------ABOUT d3dx9.h----------------------------------------
You may have to download https://www.microsoft.com/en-us/download/details.aspx?id=6812 to be able to include <d3dx9.h>
"The DirectX SDK installation will add a Property Sheet Macro called $(DXSDK_DIR) into Visual Studio. 
Instead of inserting an absolute path in your Include and Library Directories, 
I'd recommend using this macro to set the Include and Library path for DX dependencies.
As Include Directory add: $(DXSDK_DIR)Include
As Library Directory add: $(DXSDK_DIR)Lib\x86 or $(DXSDK_DIR)Lib\x64 on a 64-bit architecture""
(Read more in this article: https://stackoverflow.com/questions/17015088/missing-files-directx-sdk-d3dx9-lib-d3dx9-h)
