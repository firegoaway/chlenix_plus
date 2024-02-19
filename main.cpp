// main.cpp
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "Wall.h"
#include "Agent.h"

void renderGUI() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Define your GUI elements here
        // 1. Objects Panel
        ImGui::Begin("Objects Panel");
        // Listing of objects here
        ImGui::End();

        // 2. Toolbar/Toggles
        ImGui::Begin("Toolbar");
        if (ImGui::Button("Pointer")) {
            // Handle Pointer button click
        }
        if (ImGui::Button("Wall")) {
            // Handle Wall button click
        }

        // Repeat similarly for every tool required like Agent, Exit, Room, Bool, Slab, Device
        ImGui::End();

        // 3. Process Panel (Optional - Expand as required)
        ImGui::Begin("Process");
        // Simulations and results details
        ImGui::End();

        // 4. Scene Viewer (Optional - Expand as required)
        ImGui::Begin("Scene Viewer");
        // Render Walls in Scene
        for (auto& wall : walls) {
            auto startPoint = wall.getStartPoint();
            auto endPoint = wall.getEndPoint();
            // Convert to ImVector2, because that's what ImGui uses for points
            ImVec2 imguiStartPoint(startPoint.first, startPoint.second);
            ImVec2 imguiEndPoint(endPoint.first, endPoint.second);
            // Draw the wall as a line in ImGui
            ImGui::GetWindowDrawList()->AddLine(imguiStartPoint, imguiEndPoint, IM_COL32(255, 0, 0, 255));
        }
        // Boolean to keep track of whether we are currently creating a wall
        bool creatingWall = false;

        // Wall start point - we store this so we can create the wall when the second point is clicked
        std::pair<float, float> wallStartPoint;

        void handleSceneViewerClick(float mouseX, float mouseY) {
            if (!creatingWall) {
                // If we aren't currently creating a wall, start creating one
                creatingWall = true;
                wallStartPoint = std::make_pair(mouseX, mouseY);
            }
            else {
                // If we are currently creating a wall, finish creating it
                creatingWall = false;
                Wall newWall(wallStartPoint.first, wallStartPoint.second, mouseX, mouseY);
                walls.push_back(newWall);
            }
        }
        // In your main loop, check to see if the user clicked within the Scene Viewer
        if (ImGui::IsMouseClicked(0)) {
            float mouseX = ImGui::GetMousePos().x;
            float mouseY = ImGui::GetMousePos().y;
            // Check if click was within the Scene Viewer's screen space
            if (ImGui::Begin("Scene Viewer")) {
                handleSceneViewerClick(mouseX, mouseY);
            }
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Create a windowed mode window and an OpenGL context
    GLFWwindow* window = glfwCreateWindow(640, 480, "Fevasim", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        return -1;
    }

    // Initialize Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    while (!glfwWindowShouldClose(window)) {
        // Clear the framebuffer
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        renderGUI();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup and close the window
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
