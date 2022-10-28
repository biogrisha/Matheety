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

    const ImVec2 origin(canvas_p0.x, canvas_p0.y); // Lock scrolled origin
    const ImVec2 mouse_pos_in_canvas(io.MousePos.x - origin.x, io.MousePos.y - origin.y);

    ImGui::InvisibleButton("canvas", canvas_sz, ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);

    if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::IsItemHovered())
    {
        events.onMouseDrag(-io.MouseDelta.x, io.MouseDelta.y);
    }

    if (ImGui::IsKeyDown(ImGuiKey_W))
    {
        events.onWKey(ImGui::GetIO().DeltaTime);
    }
    if (ImGui::IsKeyDown(ImGuiKey_S))
    {
        events.onSKey(ImGui::GetIO().DeltaTime);
    }
    if (ImGui::IsKeyDown(ImGuiKey_A))
    {
        events.onAKey(ImGui::GetIO().DeltaTime);
    }
    if (ImGui::IsKeyDown(ImGuiKey_D))
    {
        events.onDKey(ImGui::GetIO().DeltaTime);
    }

    

    

    ImGui::End();
}
