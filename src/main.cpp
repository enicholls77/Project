#include <vector>
#include <iostream>
#include <format>
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

// worker table display column enums
enum WorkerTableColumns{
	WorkerSelect,
	WorkerId,
	WorkerMiningRate,
	WorkerTool,
	WorkerUpgrade
};

// class SortSpecCache {

// private:
//     static SortSpecCache* instance;

//     SortSpecCache() {
//         // private to prevent anyone else from instantiating
//     }

//  public:
// 	static const ImGuiTableSortSpecs* s_current_sort_specs;


//     static SortSpecCache* getInstance(){
//         if(!instance){
//             instance = new SortSpecCache();
//         }
//         return instance;
//     }

// };

// SortSpecCache *SortSpecCache::instance = 0;

// singleton for storing sorting spec for worker table columns

// int compareWorkers(const void* lhs, const void* rhs){
//     Worker* a = (Worker*)lhs;
//     Worker* b = (Worker*)rhs;
//     for (int n = 0; n < 2; n++)
//     {
//         // Here we identify columns using the ColumnUserID value that we ourselves passed to TableSetupColumn()
//         // We could also choose to identify columns based on their index (sort_spec->ColumnIndex), which is simpler!
// 		SortSpecCache* cache = SortSpecCache::getInstance();
//         const ImGuiTableColumnSortSpecs* sort_spec = &cache->s_current_sort_specs->Specs[n];
//         int delta = 0;
//         switch (sort_spec->ColumnUserID)
//         {
//         case WorkerId:           			delta = (a->id - b->id);                									break;
//         case WorkerMiningRate:           	delta = (a->mine() - b->mine());     										break;
//         case WorkerTool:           			delta = (strcmp(a->equippedTool->toolName.c_str(), b->equippedTool->toolName.c_str()));     break;
//         default: IM_ASSERT(0); break;
//         }
//         if (delta > 0)
//             return (sort_spec->SortDirection == ImGuiSortDirection_Ascending) ? +1 : -1;
//         if (delta < 0)
//             return (sort_spec->SortDirection == ImGuiSortDirection_Ascending) ? -1 : +1;
//     }

//     // qsort() is instable so always return a way to differenciate items.
//     // Your own compare function may want to avoid fallback on implicit sort specs e.g. a Name compare if it wasn't already part of the sort specs.
//     return (a->id - b->id);
// }


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

	Game g = Game(2400, 1);
	// historical data
	vector<int> tickHistory;
	vector<float> miningRateHistory;
	float miningRateBuffer[240];
	vector<float> workerCountHistory;
	float workerCountBuffer[240];
	Worker* selectedWorker = g.workers[0];
	
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
		bool updated = g.update();
		int day = g.day();
		int numWorkers = g.workers.size();
		double miningRate = g.getTotalMiningRate();

		if(updated){
			tickHistory.push_back(g.tick);
			if(miningRateHistory.size() >= 240){
				miningRateHistory.erase(miningRateHistory.begin());
			}
			miningRateHistory.push_back((float)miningRate);

			std::copy(miningRateHistory.begin(), miningRateHistory.end(), miningRateBuffer);

			if(workerCountHistory.size() >= 240){
				workerCountHistory.erase(workerCountHistory.begin());
			}
			workerCountHistory.push_back((float)numWorkers);

			std::copy(workerCountHistory.begin(), workerCountHistory.end(), workerCountBuffer);
		}

		ImGui::Begin("Stats");
		// Text that appears in the window
		ImGui::Text("Hello there adventurer!");
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Gold: %.2f G", g.gold);
		ImGui::Text("Score: %.2f", g.score);
		ImGui::Text("Workers: %i", numWorkers);
		ImGui::Text("Day: %i", day);
		ImGui::Text("Seconds elapsed: %.2f", g.timeElapsed);
		ImGui::Text("Powering for: %i", g.poweringFor);
		ImGui::Text("G/tick: %.2f", miningRate);
		ImGui::Text("G/day: %.2f", miningRate * 24);
		ImGui::Text("s/day: %.2f", (float) ( (float)24 / g.ticksPerSecond));
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
		float minGold = 0;
		float maxGold = 0;
		if(end > 0){
			float minGold = g.goldHistory[start];
			float maxGold = g.goldHistory[start];
		}

		int j = 0;
		for(int i=start; i<end; i++){
			float gold = (float) g.goldHistory[i];
			if(gold < minGold){
				minGold = gold;
			}
			if(gold > maxGold){
				maxGold = gold;
			}
			goldHistoryBuffer[j] = gold;
			j++;
		}

		float scoresBuffer[240];
		float minScore = 0;
		float maxScore = 0;
		if(end > 0){
			float minScore= g.scores[start];
			float maxScore = g.scores[start];
		}

		j = 0;
		for(int i=start; i<end; i++){
			float score = (float) g.scores[i];
			if(score < minScore){
				minScore = score;
			}
			if(score > maxScore){
				maxScore = score;
			}
			scoresBuffer[j] = score;
			j++;
		}

		// ImGui::ShowDemoWindow();

		ImGui::SetNextWindowSize(ImVec2(315, 200), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos(ImVec2(400,60), ImGuiCond_FirstUseEver);
		
		ImGui::Begin("Statistics - Graphs (last 240 ticks)");
		ImGui::PlotLines("Gold Balance", goldHistoryBuffer, end - start, NULL, NULL, minGold, maxGold, ImVec2(0, 50));
		ImGui::PlotLines("Score", scoresBuffer, end - start, NULL, NULL, minScore, maxScore, ImVec2(0, 50));
		ImGui::PlotLines("Workers", workerCountBuffer, workerCountHistory.size());
		ImGui::PlotLines("Mining Rate", miningRateBuffer, miningRateHistory.size());
		ImGui::End();

		ImGui::SetNextWindowSize(ImVec2(315, 300), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos(ImVec2(60,300), ImGuiCond_FirstUseEver);
		
		ImGui::Begin("Workers and Shop");

		char buyWorkerText[20];
		std::sprintf(buyWorkerText, "Buy Worker: %.1f G", g.workerPrice);
		if(ImGui::Button(buyWorkerText)){
			bool bought = g.buyWorker();
			if(bought){
				logger.AddLog("Bought Worker\n");
			} else{
				char msg[] = "Cannot buy Worker!!! (don't be poor lol)\n";
				logger.AddLog("%s", msg);
			}
		}

		char buyUpgradeAllText[30];
		std::sprintf(buyUpgradeAllText, "Upgrade All Tools %.1f G", (g.upgradeAllBasePrice*g.workersToUpgrade));
		if(ImGui::Button(buyUpgradeAllText)){
			if (g.workersToUpgrade==0){
				logger.AddLog("No workers to upgrade!\n");
			}
			else {
				bool bought = g.upgradeAll();
				if(bought){
					logger.AddLog("Upgraded All Tools!\n");
				} 
				else{
					char msg[] = "Could not upgrade tools, back to mining!\n";
					logger.AddLog("%s", msg);
				}
			}
		}

		char supplyingPowerText[30];
		std::sprintf(supplyingPowerText, "Supply Power %.1f G", (g.poweringBasePrice * g.powerableTools));
		if(ImGui::Button(supplyingPowerText)){
			if (g.powerSupplied==1){
				logger.AddLog("Power is already supplied!\n");
			}
			else if(g.powerableTools == 0){
				logger.AddLog("No tools to power!\n");
			}
			else {
				bool bought = g.powerCurrentTools();
				if(bought){
					logger.AddLog("Power supplied for 1 day! Get cracking!\n");
				} 
				else{
					char msg[] = "Could not power tools. Don't quit your day job just yet...\n";
					logger.AddLog("%s", msg);
				}
			}
		}

		for(int i=0; i<g.toolShop.size(); i++){
			char buyToolText[40];
			double priceTest = 10.0;
			std::sprintf(buyToolText, "Buy %s: %.1f G", g.toolShop[i]->toolName.c_str(), g.toolShop[i]->price);

			if(ImGui::Button(buyToolText)){
				bool bought = g.buyTool(i, selectedWorker);
				if(bought){
					logger.AddLog("Bought Tool\n");
				} else{
					char msg[] = "Cannot buy tool!!! (don't be poor lol)\n";
					logger.AddLog("%s", msg);
				}
			}
		}

		ImGui::Text("Selected Worker: %d", selectedWorker->id);
		if (ImGui::TreeNode("Workers"))
		{
			// Create item list
			// static ImVector<MyItem> items;
			// if (items.Size == 0)
			// {
			// 	items.resize(50, MyItem());
			// 	for (int n = 0; n < items.Size; n++)
			// 	{
			// 		const int template_n = n % IM_ARRAYSIZE(template_items_names);
			// 		MyItem& item = items[n];
			// 		item.ID = n;
			// 		item.Name = template_items_names[template_n];
			// 		item.Quantity = (n * n - n) % 20; // Assign default quantities
			// 	}
			// }

			// Options
			static ImGuiTableFlags flags =
				ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Sortable | ImGuiTableFlags_SortMulti
				| ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_NoBordersInBody
				| ImGuiTableFlags_ScrollY;
			// PushStyleCompact();
			// ImGui::CheckboxFlags("ImGuiTableFlags_SortMulti", &flags, ImGuiTableFlags_SortMulti);
			// ImGui::SameLine(); HelpMarker("When sorting is enabled: hold shift when clicking headers to sort on multiple column. TableGetSortSpecs() may return specs where (SpecsCount > 1).");
			// ImGui::CheckboxFlags("ImGuiTableFlags_SortTristate", &flags, ImGuiTableFlags_SortTristate);
			// ImGui::SameLine(); HelpMarker("When sorting is enabled: allow no sorting, disable default sorting. TableGetSortSpecs() may return specs where (SpecsCount == 0).");
			// PopStyleCompact();

			if (ImGui::BeginTable("table_sorting", 4, flags, ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 15), 0.0f))
			{
				// Declare columns
				// We use the "user_id" parameter of TableSetupColumn() to specify a user id that will be stored in the sort specifications.
				// This is so our sort function can identify a column given our own identifier. We could also identify them based on their index!
				// Demonstrate using a mixture of flags among available sort-related flags:
				// - ImGuiTableColumnFlags_DefaultSort
				// - ImGuiTableColumnFlags_NoSort / ImGuiTableColumnFlags_NoSortAscending / ImGuiTableColumnFlags_NoSortDescending
				// - ImGuiTableColumnFlags_PreferSortAscending / ImGuiTableColumnFlags_PreferSortDescending
				ImGui::TableSetupColumn("id",       ImGuiTableColumnFlags_DefaultSort          | ImGuiTableColumnFlags_WidthStretch,   0.0f, WorkerId);
				ImGui::TableSetupColumn("G/tick", ImGuiTableColumnFlags_PreferSortAscending | ImGuiTableColumnFlags_WidthStretch, 0.0f, WorkerMiningRate);
				ImGui::TableSetupColumn("Tool", ImGuiTableColumnFlags_PreferSortDescending | ImGuiTableColumnFlags_WidthStretch, 0.0f, WorkerTool);
				ImGui::TableSetupColumn("Upgrade", ImGuiTableColumnFlags_PreferSortDescending | ImGuiTableColumnFlags_WidthStretch, 0.0f, WorkerUpgrade);
				ImGui::TableSetupScrollFreeze(0, 1); // Make row always visible
				ImGui::TableHeadersRow();

				// TODO: Sort our data if sort specs have been changed!

				// SortSpecCache* cache = SortSpecCache::getInstance();
				// if (ImGuiTableSortSpecs* sorts_specs = ImGui::TableGetSortSpecs())
				// 	if (sorts_specs->SpecsDirty)
				// 	{
				// 		cache->s_current_sort_specs = sorts_specs; // Store in variable accessible by the sort function.
				// 		if (g.workers.size() > 1)
				// 			qsort(&g.workers[0], (size_t)g.workers.size(), sizeof(g.workers[0]), compareWorkers);
				// 		cache->s_current_sort_specs = NULL;
				// 		sorts_specs->SpecsDirty = false;
				// 	}

				// Demonstrate using clipper for large vertical lists
				ImGuiListClipper clipper;
				clipper.Begin(g.workers.size());
				while (clipper.Step())
					for (int row_n = clipper.DisplayStart; row_n < clipper.DisplayEnd; row_n++)
					{
						// Display a data item
						Worker* worker = g.workers[row_n];
						ImGui::PushID(69420); // hehe
						ImGui::TableNextRow();
						ImGui::TableNextColumn();
						char *idText;
						std::sprintf(idText, "%d", worker->id);
						if(ImGui::Selectable(idText)){ selectedWorker = worker; }
						ImGui::TableNextColumn();
						ImGui::Text("%.2f", worker->mine());
						ImGui::TableNextColumn();
						ImGui::TextUnformatted(worker->equippedTool->toolName.c_str());
						// upgrading column
						char upIcon[50];
						std::sprintf(upIcon, "UPGRADE %.2f G", g.upgradeAllBasePrice);
						bool upgraded = worker->equippedTool->upgraded;
						if(upgraded){
							std::sprintf(upIcon, "MAXXED");
						}
						ImGui::TableNextColumn();
						// TODO: only miner closest to top of table can be upgraded???
						if(ImGui::SmallButton(upIcon)){
							if(!upgraded){
								worker->equippedTool->upgrade();
								logger.AddLog("Upgraded worker\n");
							}
						}
						ImGui::PopID();
					}
				ImGui::EndTable();
			}
			ImGui::TreePop();
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