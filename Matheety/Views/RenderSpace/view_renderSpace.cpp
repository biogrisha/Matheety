#include "view_renderSpace.h"

view_renderSpace::view_renderSpace()
{
}

void view_renderSpace::Show()
{
    ImGuiIO& io = ImGui::GetIO();


    ImGui::Begin("Map");
    ImVec2 size = ImVec2(32.0f, 32.0f);
    ImVec2 uv0 = ImVec2(0.0f, 1.0f);
    ImVec2 uv1 = ImVec2(1, 0);
    ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

    ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();      // ImDrawList API uses screen coordinates!
    ImVec2 canvas_sz = ImGui::GetContentRegionAvail();
    if (canvas_sz.x < 200.0f) canvas_sz.x = 200.0f;
    if (canvas_sz.y < 200.0f) canvas_sz.y = 200.0f;
    ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);
    auto imgPos = ImGui::GetCursorPos();
    ImGui::Image((void*)(m_renderTarget), canvas_sz, uv0, uv1, tint_col, tint_col);
    ImGui::SetCursorPos(imgPos);
    ImGui::InvisibleButton("canvas", canvas_sz, ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);
    ImGui::SetItemUsingMouseWheel();

    const bool is_hovered = ImGui::IsItemHovered(); // Hovered
    const ImVec2 mouse_pos_in_canvas(io.MousePos.x - canvas_p0.x, io.MousePos.y - canvas_p0.y);
    // Add first and second point
    double xCoord = 0;
    double yCoord = 0;

    ImGui::End();
}
