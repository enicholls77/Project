#include <string>
#include <vector>
#include <iostream>
#include <cmath>

// #include <glad/glad.h>
#include "../bindings/imgui_impl_opengl3.h"
#include "../bindings/imgui_impl_glfw.h"
#include "Game.h"
#include "GuiLogger.h"

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
	// ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 410");

	// Variables to be changed in the ImGUI window
	// bool drawTriangle = true;
	float size = 1.0f;
	float color[4] = { 0.8f, 0.3f, 0.02f, 1.0f };

	// Exporting variables to shaders
	// glUseProgram(shaderProgram);
	// glUniform1f(glGetUniformLocation(shaderProgram, "size"), size);
	// glUniform4f(glGetUniformLocation(shaderProgram, "color"), color[0], color[1], color[2], color[3]);

	Game g = Game(2400, 20);
	// historical data
	vector<int> tickHistory;
	vector<double> miningRateHistory;
	static GuiLogger logger;

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

		// game updates
		g.update();
		int day = g.day();
		int numWorkers = g.workers.size();
		double miningRate = g.getTotalMiningRate();

		tickHistory.push_back(g.tick);
		miningRateHistory.push_back(miningRate);

		ImGui::Begin("Stats");
		// Text that appears in the window
		ImGui::Text("Hello there adventurer!");
		ImGui::Text("Gold: %f G", g.gold);
		ImGui::Text("Score: %f", g.score);
		ImGui::Text("Workers: %i", numWorkers);
		ImGui::Text("Day: %i", day);
		ImGui::Text("Seconds elapsed: %f", g.timeElapsed);
		ImGui::Text("g/tick: %f", miningRate);
		ImGui::Text("g/day: %f", miningRate * 24);
		ImGui::Text("s/day: %d", 24 / g.ticksPerSecond);
		// Checkbox that appears in the window
		// ImGui::Checkbox("Draw Triangle", &drawTriangle);
		// Slider that appears in the window
		// Ends the window
		ImGui::End();


		// Buffer size for all historical data is a maximum of 240 ticks 
		// (240 seconds, 10 in-game days)
		int start = g.goldHistory.size() <= 240 ? 0 : g.goldHistory.size() - 240;
		int end = g.goldHistory.size();

		float goldHistoryBuffer[240];
		int j = 0;
		for(int i=start; i<end; i++){
			goldHistoryBuffer[j] = (float) g.goldHistory[i];
			j++;
		}


		// cout << g.scores[g.tick] << endl;
		float scoresBuffer[240];
		j = 0;
		for(int i=start; i<end; i++){
			scoresBuffer[j] = (float) g.scores[i];
			j++;
		}

		float miningRateHistoryBuffer[240];
		j = 0;
		for(int i=start; i<end; i++){
			miningRateHistoryBuffer[j] = (float) miningRateHistory[i];
			j++;
		}

		ImGui::SetNextWindowSize(ImVec2(315, 200), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos(ImVec2(400,60), ImGuiCond_FirstUseEver);
		
		ImGui::Begin("Statistics - Graphs");
		ImGui::PlotLines("Gold Balance", goldHistoryBuffer, end - start);
		ImGui::PlotLines("Score", scoresBuffer, end - start);
		ImGui::PlotLines("Mining Rate", miningRateHistoryBuffer, end - start);
		ImGui::End();

		ImGui::SetNextWindowSize(ImVec2(315, 200), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos(ImVec2(60,300), ImGuiCond_FirstUseEver);
		
		ImGui::Begin("Shop");
		if(ImGui::Button("Buy Worker: 5 G")){
			bool bought = g.buyWorker();
			if(bought){
				logger.AddLog("Bought Worker\n");
			} else{
				char msg[] = "Cannot buy Worker!!! (don't be poor lol)\n";
				ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255,0,0,255));
				// ImGui::InputText("##text1", msg, sizeof(msg));
				logger.AddLog("%s", msg);
				ImGui::PopStyleColor();
			}
		}
		ImGui::End();

		ImGui::SetNextWindowSize(ImVec2(325, 200), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos(ImVec2(400,300), ImGuiCond_FirstUseEver);
		logger.Draw("Logs");


		// ImGui::End();

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