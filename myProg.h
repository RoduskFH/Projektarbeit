#pragma once

#include "imgui.h"
#include <math.h>
#include <vector>
#include <map>
#include <iostream>

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

typedef std::vector<Pair> Pixels;

/**
 *  Define the Shape in a Pair-Vector and also stores the position of given Shape
 */
struct Shape
{
    unsigned int width_;
    unsigned int height_;
    ImVec2 pos_;
    unsigned int level_;

    Shape(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int l = 0) : width_(w), height_(h), pos_(x, y), level_(l)
    {
    }
    inline int equalPixels(Shape shape2)
    {
        std::vector<Pair> shapeV_ = getPixels();
        std::vector<Pair> shapeV_2 = shape2.getPixels();
        // assert(shapeV_.size() == shapeV_2.size());
        int resultX1 = 0;
        int resultY1 = 0;
        int resultX2 = 0;
        int resultY2 = 0;
        int result = 0;
        for (size_t i = 0; i < shapeV_.size(); i++)
        {
            resultX1 = shapeV_[i].x_ + pos_.x;
            resultY1 = shapeV_[i].y_ + pos_.y;
            for (size_t j = 0; j < shapeV_2.size(); j++)
            {
                resultX2 = shapeV_2[j].x_ + shape2.pos_.x;
                resultY2 = shapeV_2[j].y_ + shape2.pos_.y;

                if (resultX1 == resultX2 && resultY1 == resultY2)
                {
                    result++;
                }
            }
        }
        return result;
    }

    inline Pixels getPixels() const
    {
        Pixels p;
        p.reserve(width_ * height_);
        for (size_t w = 0; w < width_; w++)
        {
            for (size_t h = 0; h < height_; h++)
            {
                Pair pix = {w, h};
                p.push_back(pix);
            }
        }
        return p;
    }

    inline void rotate()
    {
        int dummy = width_;
        width_ = height_;
        height_ = dummy;
    }
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
    ImVec2 scrolling_;
    ImDrawList *drw;

    Drawer(float step, const ImVec2 p0, const ImVec2 scrolling, ImDrawList *drw) : grid_step_(step), canvas_p0_(p0), scrolling_(scrolling), drw(drw)
    {
    }

    /**
     * Adds a Black Square on given Coordinates x, y
     */
    void addSqr(const int x, const int y)
    {
        ImVec2 pos(x * grid_step_ + scrolling_.x, y * grid_step_ + scrolling_.y);
        drw->AddRectFilled(canvas_p0_ + pos, canvas_p0_ + pos + ImVec2(grid_step_, grid_step_), IM_COL32(0, 0, 0, 255));
    }

    /**
     * Adds a Black Square on given Coordinates x, y
     */
    void addSqr(const int x, const int y, const int level)
    {
        ImVec2 pos(x * grid_step_ + scrolling_.x, y * grid_step_ + scrolling_.y);
        switch (level)
        {
        case 1:
            //red
            drw->AddRectFilled(canvas_p0_ + pos, canvas_p0_ + pos + ImVec2(grid_step_, grid_step_), IM_COL32(255, 0, 0, 255));
            break;
        case 2:
            //green
            drw->AddRectFilled(canvas_p0_ + pos, canvas_p0_ + pos + ImVec2(grid_step_, grid_step_), IM_COL32(0, 255, 0, 255));
            break;
        case 3:
            //blue
            drw->AddRectFilled(canvas_p0_ + pos, canvas_p0_ + pos + ImVec2(grid_step_, grid_step_), IM_COL32(0, 0, 255, 255));
            break;
        default:
            drw->AddRectFilled(canvas_p0_ + pos, canvas_p0_ + pos + ImVec2(grid_step_, grid_step_), IM_COL32(0, 0, 0, 255));
            break;
        }
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
        switch (s.level_)
        {
        case 0:
            for (auto pixel : s.getPixels())
            {
                addSqr(pixel.x_ + pos.x, pixel.y_ + pos.y);
            }
            break;
        default:
            for (auto pixel : s.getPixels())
            {
                addSqr(pixel.x_ + pos.x, pixel.y_ + pos.y, s.level_);
            }
            break;
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

static unsigned int maxLevel(std::vector<Shape> &shapes)
{
    unsigned int maxLevel = 0;
    for (auto s : shapes)
    {
        if (s.level_ > maxLevel)
        {
            maxLevel = s.level_;
        }
    }
    return maxLevel;
}

static bool canStackShape(std::vector<Shape> &shapes, Shape s, unsigned int level)
{
    int result = 0;
    bool canStack = false;

    if (level == 0)
    {
        canStack = true;
        std::cout << "HERP " << canStack << std::endl;
    }
    else
    {
        for (auto &sha : shapes)
        {
            if (sha.level_ == level - 1)
            {
                result += sha.equalPixels(s);
                if (result >= 2)
                {
                    canStack = true;
                    break;
                }
            }
        }
    }

    if (!canStack)
    {
        return false;
    }

    /**
     * This checks if there are collisions on the same level
     */
    for (auto &sha : shapes)
    {
        if (sha.level_ == level && sha.equalPixels(s))
        {
            return false;
        }
    }
    return true;
}

static bool stackShape(std::vector<Shape> &shapes, Shape s, unsigned int level)
{
    if (!canStackShape(shapes, s, level))
    {
        return false;
    }
    s.level_ = level;
    shapes.push_back(s);
    return true;
}

static void myProg()
{
    static int currentLevel = 0;
    static int currX = 0;
    static int currY = 0;
    static int currH = 1;
    static int currW = 1;
    static int counter = 0;
    static std::vector<Shape> shapes;

    ImGui::Begin("HERPY! OWO"); // Create a window called "Hello, world!" and append into it.

    ImGui::SliderInt("Level", &currentLevel, 0, 10); // Edit 1 float using a slider from 0.0f to 1.0f

    ImGui::SliderInt("X", &currX, 0, 10);

    ImGui::SliderInt("Y", &currY, 0, 10);

    ImGui::SliderInt("Height", &currH, 1, 10);

    ImGui::SliderInt("Width", &currW, 1, 10);

    Shape dummy(currX, currY, currW, currH, currentLevel);
    if (ImGui::Button("Add Shape")) // Buttons return true when clicked (most widgets return true when edited/activated)
    {
        stackShape(shapes, Shape(currX, currY, currW, currH), currentLevel);
    }
    ImGui::SameLine();
    ImGui::Text("counter = %i", (int)shapes.size());

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

        Drawer dr = Drawer(GRID_STEP, canvas_p0, scrolling, draw_list);

        //Create Rectangular Shape in coordinates 0, 0
        // Shape rectangle = {{{0, 0}, {1, 0}, {0, 1}, {1, 1}, {0, 2}, {1, 2}}, {0, 0}, 0};
        Shape rectangle(0, 0, 2, 3);
        Shape rectangle2(currX, currY, currW, currH);
        Shape rectangle1(1, 2, 2, 3);
        // Shape rectangle1 = {{{0, 0}, {1, 0}, {0, 1}, {1, 1}, {0, 2}, {1, 2}}, {4, 4}, 0};
        // Shape rectangle2 = {{{0, 0}, {1, 0}, {0, 1}, {1, 1}, {0, 2}, {1, 2}}, {6, 4}, 0};
        // Shape rectangle3 = {{{0, 0}, {1, 0}, {0, 1}, {1, 1}, {0, 2}, {1, 2}}, {1, 1}, 0};
        // Shape rectangle4 = {{{0, 0}, {1, 0}, {0, 1}, {1, 1}, {0, 2}, {1, 2}}, {2, 3}, 0};

        //TODO Push this outside run loop??

        // std::cout << stackShape(shapes, rectangle, 0) << std::endl;
        // stackShape(shapes, rectangle1, 0);
        // stackShape(shapes, rectangle1, 1);
        // stackShape(shapes, rectangle2, currentLevel);
        /**
         * Comparing the 2 Shape vectors to see how many pixels are equal on each vector
         */
        // dr.addShape(rectangle);
        int result = 0;
        for (auto &s : shapes)
        {
            if (currentLevel == s.level_ || s.level_ + 1 == currentLevel)
            {
                dr.addShape(s);
            }
        }
        static unsigned int blink = 30;
        if (canStackShape(shapes, dummy, currentLevel) && blink > 30)
        {
            dr.addShape(dummy);
        }
        blink--;
        if (blink == 0)
        {
            blink = 60;
        }

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

        /**
         * Pop all the shapes so Size remains true
         */
        // for (auto shape : shapes)
        // {
        //     shapes.pop_back();
        // }
    }

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}
