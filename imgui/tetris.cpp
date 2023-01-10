#include "tetris.h"

#include "imgui.h"

void ShowTetris()
{
   ImGui::Begin("Tetris");

//SetNextWindowSize does not work.
   ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);
   ImDrawList* draw_list = ImGui::GetWindowDrawList();

   ImVec4 colf = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
   const ImU32 col = ImColor(colf);

   const ImVec2 originPosition = ImGui::GetCursorScreenPos();
   ImVec2 p1 = ImVec2(originPosition.x + 200.0f, originPosition.y + 200.0f);
   draw_list->AddRectFilled(originPosition, p1, col, 10.0f);

   ImGui::End();
}
