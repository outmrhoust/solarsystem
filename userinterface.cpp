#include "userinterface.h"
#include "./imgui/imgui.h"
#include "./imgui/backends/imgui_impl_glfw.h"
#include "./imgui/backends/imgui_impl_opengl3.h"

UserInterface::UserInterface(PointLight *m_pl, GLFWwindow* window)
    :m_pl(m_pl),m_rotationSpeed(1.0f)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
    ImGui::StyleColorsDark();
}

UserInterface::~UserInterface()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}




void UserInterface::Bind( Shader *shader)
{
    shader->setUniform3fv("pointLightColor", m_pl->color);
    shader->setUniform1f("pointLightPower", m_pl->power);
}

void UserInterface::Draw()
{

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(350, 100), ImGuiCond_Always);

    ImGui::Begin("settings", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);



    ImGui::SliderFloat("Speed", &m_rotationSpeed, 0, 10);

    ImGui::ColorEdit3("light  Color", (float*)&m_pl->color);

    ImGui::SliderFloat("light power", (float*)&m_pl->power, 0, 10000);

    ImGui::End();

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


