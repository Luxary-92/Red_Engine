#include "ModuleEditor.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "ImGui/imgui.h"
#include "ImGui/backends/imgui_impl_opengl3.h"
#include "ImGui/backends/imgui_impl_sdl2.h"


ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app, start_enabled)
{
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
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Editor Windows"))
        {
            if (ImGui::MenuItem("Console")) {

            }
            if (ImGui::MenuItem("Configuration")) {

            }
            if (ImGui::MenuItem("Hierarchy")) {

            }
            if (ImGui::MenuItem("Inspector")) {

            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("About"))
        {
            ImGui::Text("Red Engine");ImGui::NewLine();

            ImGui::Text("Engine created for the subject of VideoGame Engines Created by Nixon Daniel Correa Albarracin & Enric Arxer Cortes");
            ImGui::Text("Github page : https://github.com/Luxary-92/Red_Engine");ImGui::NewLine();

            if (ImGui::MenuItem("Github : Red Engine")) {
                ShellExecute(0, 0, "https://github.com/Luxary-92/Red_Engine", 0, 0, SW_SHOW);
            }
            
            ImGui::Text("License:");ImGui::NewLine();

            ImGui::TextWrapped("Copyright (c) 2023 Luxary"); ImGui::NewLine();

            ImGui::TextWrapped("Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the 'Software'), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and to permit persons to whom the Software i furnished to do so, subject to the following conditions : "); 
            ImGui::NewLine();

            ImGui::TextWrapped("The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software."); 
            ImGui::NewLine();

            ImGui::TextWrapped("THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE."); 
            ImGui::NewLine();

            ImGui::EndMenu();
        }
        if (ImGui::Button("Close"))
        {
            //here to close the app
            App->AppClose = true;
        }
        ImGui::EndMainMenuBar();
    }
    //Consloe
    if (ImGui::Begin("Console"))
    {
        ImGui::TextWrapped("The window should LOG the geometry loading process from ASSIMP and the external libraries initialization process");

        ImGui::End();
    }
    //Configuration
    if (ImGui::Begin("Configuration"))
    {
        //Frames and miliseconds
        frames = App->GetFR();
        AddFPS(frames);
        milisecods = App->GetDT();
        AddMS(milisecods);

        ImGui::BulletText(""); ImGui::TextWrapped("A graph for the frames per second");

        ImGui::PlotHistogram("", framesLog.data(), framesLog.size(),0, "FPS", 0.0f, 100.0f, ImVec2(200, 100));
        ImGui::PlotHistogram("", milisecodsLog.data(), milisecodsLog.size(), 0, "Miliseconds", 0.0f, 0.03f, ImVec2(200, 100));

        ImGui::BulletText(""); ImGui::TextWrapped("Configuration for all variables on each module (renderer, window, input, textures)");
        ImGui::BulletText(""); ImGui::TextWrapped("Information output of memory consumption, hardware detection and software versions(SDL, OpenGL, DevIL).");

        ImGui::End();
    }
    //Hierarchy
    if (ImGui::Begin("Hierarchy"))
    {
        ImGui::TextWrapped("you should display a list with all GameObjects in this window. The user should be able to select a GameObject through this window ");

        ImGui::End();
    }
    //Inspector
    if (ImGui::Begin("Inspector"))
    {
        ImGui::TextWrapped("You should display information about the components of the selected GameObject");

        ImGui::BulletText("");ImGui::TextWrapped("Transform: only for display purposes. Show position, rotation and scale for the selected GameObject.");

        ImGui::BulletText("");ImGui::TextWrapped("Mesh: information about the loaded mesh. There should be an option to display its normals(per - triangle and per - face).");

        ImGui::BulletText("");ImGui::TextWrapped("Texture: display texture size and path.There should be an option to view the selected GameObject with the checkers texture.");

        ImGui::End();
    }
    //ImGui::ShowDemoWindow();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool ModuleEditor::CleanUp()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

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