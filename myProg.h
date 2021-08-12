#pragma once

#include "imgui.h"
#include <math.h>
#include <vector>

static inline ImVec2 operator*(const ImVec2 &lhs, const float rhs) { return ImVec2(lhs.x * rhs, lhs.y * rhs); }
static inline ImVec2 operator/(const ImVec2 &lhs, const float rhs) { return ImVec2(lhs.x / rhs, lhs.y / rhs); }
static inline ImVec2 operator+(const ImVec2 &lhs, const ImVec2 &rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
static inline ImVec2 operator-(const ImVec2 &lhs, const ImVec2 &rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }
static inline ImVec2 operator*(const ImVec2 &lhs, const ImVec2 &rhs) { return ImVec2(lhs.x * rhs.x, lhs.y * rhs.y); }
static inline ImVec2 operator/(const ImVec2 &lhs, const ImVec2 &rhs) { return ImVec2(lhs.x / rhs.x, lhs.y / rhs.y); }
static inline ImVec2 &operator*=(ImVec2 &lhs, const float rhs)
{
    lhs.x *= rhs;
    lhs.y *= rhs;
    return lhs;
}
static inline ImVec2 &operator/=(ImVec2 &lhs, const float rhs)
{
    lhs.x /= rhs;
    lhs.y /= rhs;
    return lhs;
}
static inline ImVec2 &operator+=(ImVec2 &lhs, const ImVec2 &rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}
static inline ImVec2 &operator-=(ImVec2 &lhs, const ImVec2 &rhs)
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
}
static inline ImVec2 &operator*=(ImVec2 &lhs, const ImVec2 &rhs)
{
    lhs.x *= rhs.x;
    lhs.y *= rhs.y;
    return lhs;
}
static inline ImVec2 &operator/=(ImVec2 &lhs, const ImVec2 &rhs)
{
    lhs.x /= rhs.x;
    lhs.y /= rhs.y;
    return lhs;
}
static inline ImVec4 operator+(const ImVec4 &lhs, const ImVec4 &rhs) { return ImVec4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w); }
static inline ImVec4 operator-(const ImVec4 &lhs, const ImVec4 &rhs) { return ImVec4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w); }
static inline ImVec4 operator*(const ImVec4 &lhs, const ImVec4 &rhs) { return ImVec4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w); }

/**
 *  For drawing a square in coordinates x, y  
 */
struct Pair
{
    int x_;
    int y_;
};

/**
 *  Define the Shape in a Pair-Vector and also stores the position of given Shape
 */
struct Shape
{
    std::vector<Pair> shapeV_;
    ImVec2 pos_;
};

/**
 * Grid Step
 * Canvas Starting Point
 * Draw List
 */
struct Drawer
{
    float grid_step_;
    ImVec2 canvas_p0_;
    ImDrawList *drw;

    Drawer(float step, const ImVec2 p0, ImDrawList *drw) : grid_step_(step), canvas_p0_(p0), drw(drw)
    {
    }

    /**
     * Adds a Black Square on given Coordinates x, y
     */
    void addSqr(const int x, const int y)
    {
        ImVec2 pos(x * grid_step_, y * grid_step_);
        drw->AddRectFilled(canvas_p0_ + pos, canvas_p0_ + pos + ImVec2(grid_step_, grid_step_), IM_COL32(0, 0, 0, 255));
    }

    /**
     * Adds a Black Square on given Cooridinates from Pair
     */
    void addSqr(const Pair &pair)
    {
        addSqr(pair.x_, pair.y_);
    }

    /**
    * Adds a shape on Coordinates from pos 
    */
    void addShape(const Shape &s, const ImVec2 &pos)
    {
        for (auto pixel : s.shapeV_)
        {
            addSqr(pixel.x_ + pos.x, pixel.y_ + pos.y);
        }
    }

    /**
     * Adds a shape on Coordinates given by the Shape
     */ 
    void addShape(const Shape &s)
    {
        addShape(s, s.pos_);
    }
};

static void myProg()
{
    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text."); // Display some text (you can use a format strings too)

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f); // Edit 1 float using a slider from 0.0f to 1.0f

    if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    {
        static ImVector<ImVec2> points;
        static ImVec2 scrolling(0.0f, 0.0f);
        static bool opt_enable_grid = true;
        static bool opt_enable_context_menu = true;
        static bool adding_line = false;

        ImGui::Checkbox("Enable grid", &opt_enable_grid);
        ImGui::Checkbox("Enable context menu", &opt_enable_context_menu);
        ImGui::Text("Mouse Left: drag to add lines,\nMouse Right: drag to scroll, click for context menu.");

        // Typically you would use a BeginChild()/EndChild() pair to benefit from a clipping region + own scrolling.
        // Here we demonstrate that this can be replaced by simple offsetting + custom drawing + PushClipRect/PopClipRect() calls.
        // To use a child window instead we could use, e.g:
        //      ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));      // Disable padding
        //      ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(50, 50, 50, 255));  // Set a background color
        //      ImGui::BeginChild("canvas", ImVec2(0.0f, 0.0f), true, ImGuiWindowFlags_NoMove);
        //      ImGui::PopStyleColor();
        //      ImGui::PopStyleVar();
        //      [...]
        //      ImGui::EndChild();

        // Using InvisibleButton() as a convenience 1) it will advance the layout cursor and 2) allows us to use IsItemHovered()/IsItemActive()
        static ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();    // ImDrawList API uses screen coordinates!
        static ImVec2 canvas_sz = ImGui::GetContentRegionAvail(); // Resize canvas to what's available
        if (canvas_sz.x < 50.0f)
            canvas_sz.x = 50.0f;
        if (canvas_sz.y < 50.0f)
            canvas_sz.y = 50.0f;
        ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);

        // Draw border and background color
        ImGuiIO &io = ImGui::GetIO();
        ImDrawList *draw_list = ImGui::GetWindowDrawList();
        draw_list->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(50, 50, 50, 255));
        draw_list->AddRect(canvas_p0, canvas_p1, IM_COL32(255, 255, 255, 255));

        //fdsafdsafdsa
        static const float GRID_STEP = 64.0f;

        ImVec2 p0 = ImVec2(GRID_STEP + canvas_p0.x, GRID_STEP + canvas_p0.y);
        ImVec2 p1 = ImVec2(2 * GRID_STEP + canvas_p0.x, 2 * GRID_STEP + canvas_p0.y);

        Drawer dr = Drawer(GRID_STEP, canvas_p0, draw_list);

        //Create a Square-Shape in coordinates 0, 0
        Shape sq = {{{0, 0}, {1, 0}, {0, 1}, {1, 1}}, {0, 0}};

        //Create Rectangular Shape in coordinates 0, 0
        Shape rectangle = {{{0, 0}, {1, 0}, {0, 1}, {1, 1}, {0, 2}, {1, 2}}, {0, 0}};

        //Draw Square-Shape
        // dr.addShape(sq);

        //Draw Rectangular Shape
        // dr.addShape(rectangle);

        //Single Square in coordinates 1,1
        dr.addSqr(1, 1);
        // dr.addSqr({1,1});

        // drawer::addShape(draw_list, sq);

        // draw_list->AddRectFilled(p0 + p1, p1, IM_COL32(0, 0, 0, 255));

        // This will catch our interactions
        ImGui::InvisibleButton("canvas", canvas_sz, ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);
        const bool is_hovered = ImGui::IsItemHovered();                            // Hovered
        const bool is_active = ImGui::IsItemActive();                              // Held
        const ImVec2 origin(canvas_p0.x + scrolling.x, canvas_p0.y + scrolling.y); // Lock scrolled origin
        const ImVec2 mouse_pos_in_canvas(io.MousePos.x - origin.x, io.MousePos.y - origin.y);

        // Add first and second point
        if (is_hovered && !adding_line && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
            points.push_back(mouse_pos_in_canvas);
            points.push_back(mouse_pos_in_canvas);
            adding_line = true;
        }
        if (adding_line)
        {
            points.back() = mouse_pos_in_canvas;
            if (!ImGui::IsMouseDown(ImGuiMouseButton_Left))
                adding_line = false;
        }

        // Pan (we use a zero mouse threshold when there's no context menu)
        // You may decide to make that threshold dynamic based on whether the mouse is hovering something etc.
        const float mouse_threshold_for_pan = opt_enable_context_menu ? -1.0f : 0.0f;
        if (is_active && ImGui::IsMouseDragging(ImGuiMouseButton_Right, mouse_threshold_for_pan))
        {
            scrolling.x += io.MouseDelta.x;
            scrolling.y += io.MouseDelta.y;
        }

        // Context menu (under default mouse threshold)
        ImVec2 drag_delta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Right);
        if (opt_enable_context_menu && ImGui::IsMouseReleased(ImGuiMouseButton_Right) && drag_delta.x == 0.0f && drag_delta.y == 0.0f)
            ImGui::OpenPopupOnItemClick("context");
        if (ImGui::BeginPopup("context"))
        {
            if (adding_line)
                points.resize(points.size() - 2);
            adding_line = false;
            if (ImGui::MenuItem("Remove one", NULL, false, points.Size > 0))
            {
                points.resize(points.size() - 2);
            }
            if (ImGui::MenuItem("Remove all", NULL, false, points.Size > 0))
            {
                points.clear();
            }
            ImGui::EndPopup();
        }

        // Draw grid + all lines in the canvas
        draw_list->PushClipRect(canvas_p0, canvas_p1, true);
        if (opt_enable_grid)
        {
            for (float x = fmodf(scrolling.x, GRID_STEP); x < canvas_sz.x; x += GRID_STEP)
                draw_list->AddLine(ImVec2(canvas_p0.x + x, canvas_p0.y), ImVec2(canvas_p0.x + x, canvas_p1.y), IM_COL32(200, 200, 200, 40));
            for (float y = fmodf(scrolling.y, GRID_STEP); y < canvas_sz.y; y += GRID_STEP)
                draw_list->AddLine(ImVec2(canvas_p0.x, canvas_p0.y + y), ImVec2(canvas_p1.x, canvas_p0.y + y), IM_COL32(200, 200, 200, 40));
        }
        for (int n = 0; n < points.Size; n += 2)
            draw_list->AddLine(ImVec2(origin.x + points[n].x, origin.y + points[n].y), ImVec2(origin.x + points[n + 1].x, origin.y + points[n + 1].y), IM_COL32(255, 255, 0, 255), 2.0f);
        draw_list->PopClipRect();
    }

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}

static bool searcher()
{
    // TODO
}