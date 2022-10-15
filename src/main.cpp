#include <string.h>
#include <vector>
#include <iostream>
#include <cmath>

// #include <glad/glad.h>
#include "imgui.h"
#include "../bindings/imgui_impl_opengl3.h"
#include "../bindings/imgui_impl_glfw.h"

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

void error_callback( int error, const char *msg ) {
    std::string s;
    s = " [" + std::to_string(error) + "] " + msg + '\n';
    std::cerr << s << std::endl;
}

int main()
{
	glfwSetErrorCallback( error_callback );
	// Initialize GLFW
	if(!glfwInit()){
		std::cout << "Failed init glfw" << std::endl;
    return -1;
	}

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(800, 800, "ImGui", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);

	// Initialize ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 410");

	// Variables to be changed in the ImGUI window
	bool drawTriangle = true;
	float size = 1.0f;
	float color[4] = { 0.8f, 0.3f, 0.02f, 1.0f };

	// Exporting variables to shaders
	// glUseProgram(shaderProgram);
	// glUniform1f(glGetUniformLocation(shaderProgram, "size"), size);
	// glUniform4f(glGetUniformLocation(shaderProgram, "color"), color[0], color[1], color[2], color[3]);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);

		// Tell OpenGL a new frame is about to begin
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		

		// // Tell OpenGL which Shader Program we want to use
		// glUseProgram(shaderProgram);
		// // Bind the VAO so OpenGL knows to use it
		// glBindVertexArray(VAO);
		// // Only draw the triangle if the ImGUI checkbox is ticked
		// if (drawTriangle)
		// 	// Draw the triangle using the GL_TRIANGLES primitive
		// 	glDrawArrays(GL_TRIANGLES, 0, 3);

		// ImGUI window creation
		ImGui::Begin("My name is window, ImGUI window");
		// Text that appears in the window
		ImGui::Text("Hello there adventurer!");
		// Checkbox that appears in the window
		// ImGui::Checkbox("Draw Triangle", &drawTriangle);
		// Slider that appears in the window
		ImGui::SliderFloat("Size", &size, 0.5f, 2.0f);
		// Fancy color editor that appears in the window
		ImGui::ColorEdit4("Color", color);
		// Ends the window
		ImGui::End();

		// Export variables to shader
		// glUseProgram(shaderProgram);
		// glUniform1f(glGetUniformLocation(shaderProgram, "size"), size);
		// glUniform4f(glGetUniformLocation(shaderProgram, "color"), color[0], color[1], color[2], color[3]);

		// Renders the ImGUI elements
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Deletes all ImGUI instances
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}