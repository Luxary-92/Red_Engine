#include "ModuleEditor.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "ImGui/imgui.h"
#include "ImGui/backends/imgui_impl_opengl3.h"
#include "ImGui/backends/imgui_impl_sdl2.h"


ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app, start_enabled)
{
    logs = new std::deque<std::string>();
}
        
ModuleEditor::~ModuleEditor()
{
}

bool ModuleEditor::Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
    ImGui_ImplOpenGL3_Init();

 /*   mFPSLog.reserve(30);*/

    return true;
}

void ModuleEditor::DrawEditor()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoNavFocus;

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::Begin("DockSpace", nullptr, window_flags);

    ImGui::PopStyleVar(3);

    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

    ImGui::End();

    //Top Menu barr
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            ImGui::Text("FILES");
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Assets"))
        {
            ImGui::Text("ASSETS");
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("GameObjects"))
        {
            if (ImGui::MenuItem("Cube")) {
                //drawcube
                App->renderer3D->cube();
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Windows"))
        {
            if (ImGui::MenuItem("Configuration", nullptr, ConfigState)) {
                ConfigState = !ConfigState;
            }
            if (ImGui::MenuItem("Hierarchy", nullptr, HierarchyState)) {
                HierarchyState = !HierarchyState;
            }
            if (ImGui::MenuItem("Inspector", nullptr, InspectorState)) {
                InspectorState = !InspectorState;
            }
            if (ImGui::MenuItem("Console", nullptr, ConsoleState)) {
                ConsoleState = !ConsoleState;
            }
            if (ImGui::MenuItem("Assets", nullptr, ConsoleState)) {
                AssetsState = !AssetsState;
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("About"))
        {
            ImGui::Text("Red Engine"); ImGui::NewLine();

            if (ImGui::CollapsingHeader("Project Info", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::Text("Engine created for the subject of VideoGame Engines Created by : ");

                ImGui::NewLine();
                if (ImGui::MenuItem("Nixon Daniel Correa Albarracin")) {
                    ShellExecute(0, 0, "https://github.com/Nixonbit3", 0, 0, SW_SHOW);
                }
                ImGui::Text("&");
                if (ImGui::MenuItem("Enric Arxer Cortes")) {
                    ShellExecute(0, 0, "https://github.com/Luxary-92", 0, 0, SW_SHOW);
                }
                ImGui::NewLine();
                if (ImGui::MenuItem("Github page : https://github.com/Luxary-92/Red_Engine")) {
                    ShellExecute(0, 0, "https://github.com/Luxary-92/Red_Engine", 0, 0, SW_SHOW);
                }
            }

            if (ImGui::CollapsingHeader("3r Party Libraries", ImGuiTreeNodeFlags_DefaultOpen))
            {
                //Sdl
                ImGui::NewLine();
                SDL_version version;
                SDL_GetVersion(&version);
                ImGui::BulletText("SDL %i.%i.%i", version.major, version.minor, version.patch);
                if (ImGui::MenuItem("WEB -> Libsdl.org"))
                {
                    ShellExecute(NULL, "open", "https://www.libsdl.org/", NULL, NULL, SW_SHOW);
                }
                //ImGui
                ImGui::NewLine();
                const char* version_gui = ImGui::GetVersion();
                ImGui::BulletText("ImGui %s", version_gui);
                if (ImGui::MenuItem("WEB -> Github ImGui"))
                {
                    ShellExecute(NULL, "open", "https://github.com/ocornut/imgui", NULL, NULL, SW_SHOW);
                }
                //OpenGl
                ImGui::NewLine();
                ImGui::BulletText("OpenGL %s", glGetString(GL_VERSION));
                ImGui::BulletText("Vendor: %s", glGetString(GL_VENDOR));
                ImGui::BulletText("GLSL: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
                if (ImGui::MenuItem("WEB -> Opengl.org"))
                {
                    ShellExecute(NULL, "open", "https://www.opengl.org/", NULL, NULL, SW_SHOW);
                }
                //Glew
                ImGui::NewLine();
                ImGui::BulletText("Glew %s", glewGetString(GLEW_VERSION));
                if (ImGui::MenuItem("WEB -> Glew.sourceforge.net"))
                {
                    ShellExecute(NULL, "open", "https://glew.sourceforge.net/", NULL, NULL, SW_SHOW);
                }
                //MathGeoLib
                ImGui::NewLine();
                ImGui::BulletText("MathGeoLib 2/11/2023");
                if (ImGui::MenuItem("WEB -> Github MathGeoLib"))
                {
                    ShellExecute(NULL, "open", "https://github.com/juj/MathGeoLib/commit/55053da5e3e55a83043af7324944407b174c3724", NULL, NULL, SW_SHOW);
                }
            }
            //License
            if (ImGui::CollapsingHeader("License", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::Text("License:"); ImGui::NewLine();
                ImGui::TextWrapped("Copyright (c) 2023 Luxary"); ImGui::NewLine();
                ImGui::TextWrapped("Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the 'Software'), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and to permit persons to whom the Software i furnished to do so, subject to the following conditions : ");
                ImGui::NewLine();
                ImGui::TextWrapped("The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.");
                ImGui::NewLine();
                ImGui::TextWrapped("THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.");
                ImGui::NewLine();
            }

            ImGui::EndMenu();
        }
        if (ImGui::Button("Close"))
        {
            //here to close the app
            App->AppClose = true;
        }
        if (ImGui::Button("Play"))
        {

        }
        if (ImGui::Button("Stop"))
        {

        }
        if (ImGui::Button("Pause"))
        {

        }

        ImGui::EndMainMenuBar();
    }

    //Consloe
    ConsoleWindow(ConsoleState);
    //Configuration
    ConfigurationWindow(ConfigState);
    //Hierarchy
    HierarchyWindow(HierarchyState);
    //Inspector
    InspectorWindow(InspectorState);
    //Assets
    AssetsWindow(AssetsState);

    //ImGui::ShowDemoWindow();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool ModuleEditor::CleanUp()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    framesLog.clear();
    milisecodsLog.clear();
    logs->clear();
    AllGameObjects.clear();


    return true;
}

void ModuleEditor::AddFPS(const float aFPS)
{
    if (framesLog.size() < framesShown)
    {
        framesLog.push_back(aFPS);
    }
    else
    {
        for (unsigned int i = 0; i < framesLog.size(); i++)
        {
            if (i + 1 < framesLog.size())
            {
                float iCopy = framesLog[i + 1];
                framesLog[i] = iCopy;
            }
        }
        framesLog[framesLog.size() - 1] = aFPS;
    }
}
void ModuleEditor::AddMS(const float aDT)
{
    if (milisecodsLog.size() < milisecodsShown)
    {
        milisecodsLog.push_back(aDT);
    }
    else
    {
        for (unsigned int i = 0; i < milisecodsLog.size(); i++)
        {
            if (i + 1 < milisecodsLog.size())
            {
                float iCopy = milisecodsLog[i + 1];
                milisecodsLog[i] = iCopy;
            }
        }
        milisecodsLog[milisecodsLog.size() - 1] = aDT;
    }
}


//Consloe
void ModuleEditor::ConsoleWindow(bool& State)
{
    ImGui::SetNextWindowSize(ImVec2(920, 300), ImGuiCond_FirstUseEver);
    ImGui::Begin("Console", &ConsoleState, ImGuiWindowFlags_MenuBar); {

        ImGui::TextWrapped("The window should LOG the geometry loading process from ASSIMP and the external libraries initialization process");
        ImGui::End();
    }

}

//Configuration
void ModuleEditor::ConfigurationWindow(bool& State)
{
    ImGui::Begin("Configuration", &ConfigState, ImGuiWindowFlags_MenuBar); {

        //Frames and miliseconds
        frames = App->GetFR();
        AddFPS(frames);
        milisecods = App->GetDT();
        AddMS(milisecods);

        if (ImGui::CollapsingHeader("Framerate", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::PlotHistogram("", framesLog.data(), framesLog.size(), 0, "FPS", 0.0f, 100.0f, ImVec2(200, 100));
            ImGui::PlotHistogram("", milisecodsLog.data(), milisecodsLog.size(), 0, "Miliseconds", 0.0f, 0.03f, ImVec2(200, 100));
        }
        if (ImGui::CollapsingHeader("Renderer", ImGuiTreeNodeFlags_DefaultOpen))
        {
            SDL_version version;
            SDL_GetVersion(&version);
            ImGui::BulletText("SDL %i.%i.%i", version.major, version.minor, version.patch);

            const char* version_gui = ImGui::GetVersion();
            ImGui::BulletText("ImGui %s", version_gui);

            ImGui::BulletText("OpenGL %s", glGetString(GL_VERSION));
            ImGui::BulletText("GPU-> %s", glGetString(GL_VENDOR));
            ImGui::BulletText("Brand-> %s", glGetString(GL_RENDERER));

            ImGui::BulletText("CPU -> %d", SDL_GetCPUCount());
            ImGui::BulletText("RAM -> %.1fGb", SDL_GetSystemRAM() / 1000.f);

            if (ImGui::Checkbox("Wireframe", &wireframe))
                (wireframe) ? glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) : glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

            ImGui::SameLine();

            if (ImGui::Checkbox("Depth Test", &depth_test))
                (depth_test) ? glDisable(GL_DEPTH_TEST) : glEnable(GL_DEPTH_TEST);

            if (ImGui::Checkbox("Cull Face", &cull_face))
                (cull_face) ? glDisable(GL_CULL_FACE) : glEnable(GL_CULL_FACE);

            ImGui::SameLine();

            if (ImGui::Checkbox("Color Material", &color_material))
                (color_material) ? glDisable(GL_COLOR_MATERIAL) : glEnable(GL_COLOR_MATERIAL);

            if (ImGui::Checkbox("Lighting", &lighting))
                (lighting) ? glEnable(GL_LIGHTING) : glDisable(GL_LIGHTING) ;

            ImGui::SameLine();

            if (ImGui::Checkbox("Texture 2D", &texture_2d))
                (texture_2d) ? glDisable(GL_TEXTURE_2D) : glEnable(GL_TEXTURE_2D);

        }
        if (ImGui::CollapsingHeader("Window", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Text("Screen Width"); ImGui::NewLine();
            ImGui::SameLine();
            ImGui::SliderInt(" ", &screen_width, 640, 1920);

            ImGui::Text("Screen Height"); ImGui::NewLine();
            ImGui::SameLine();
            ImGui::SliderInt(" ", &screen_height, 480, 1080);
            if (ImGui::Checkbox("FullScreen", &fullscreen));
            ImGui::SameLine();
            if (ImGui::Checkbox("Borderless", &borderless));

            if (ImGui::Button("[APPLY]")) {

                App->window->SettingsScreen(screen_width, screen_height, fullscreen, borderless);
            }
            ImGui::SameLine();
            if (ImGui::Button("[DEFAULT]")) {

                App->window->SettingsScreen(1280, 800, false, false);
            }
        }
        if (ImGui::CollapsingHeader("Input", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::TextWrapped("Camera Rotation Speed");
            ImGui::TextWrapped("Camera Movement Speed");
        }

        ImGui::End();
    
    }

}

//Hierarchy
void ModuleEditor::HierarchyWindow(bool& State)
{


    ImGui::Begin("Hierarchy", &HierarchyState, ImGuiWindowFlags_MenuBar); {

        //std::vector<GameObject*> Object_List = App->scene;

        //for (uint i = 0; i < Object_List.size(); i++)
        //{
        //    DrawHierarchyLevel(Object_List[i]);
        //}


        ImGui::TextWrapped("you should display a list with all GameObjects in this window. The user should be able to select a GameObject through this window "); ImGui::NewLine();
        
    }
    ImGui::End();

}


//Inspector
void ModuleEditor::InspectorWindow(bool& State)
{
    ImGui::Begin("Inspector", &InspectorState, ImGuiWindowFlags_MenuBar); {

        if (Selectet_GameObject != NULL)
        {
            ImGui::Text(Selectet_GameObject->Object_Name.c_str());
            ImGui::Checkbox("Active", &Selectet_GameObject->active);
            ImGui::NewLine;
            strcpy(NewName, Selectet_GameObject->Object_Name.c_str());
            if (ImGui::InputText(" ", &NewName[0], sizeof(NewName)))
            {
                Selectet_GameObject->Object_Name = NewName;
            }
            ImGui::NewLine();

            for (uint m = 0; m < Selectet_GameObject->Components.size(); m++)
            {
                if (Selectet_GameObject->selected)
                {
                    Selectet_GameObject->Components[m]->Inspector_Info();
                }
            }         
        }
    }
    ImGui::End();
}

//Assets
void ModuleEditor::AssetsWindow(bool& State)
{
    ImGui::Begin("Assets", &AssetsState, ImGuiWindowFlags_MenuBar); {

        ImGui::TextWrapped("shows all user assets * it can be a simple tree viewer"); ImGui::NewLine();

        ImGui::End();
    }

}

