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

/**
 *  Define the Shape in a Pair-Vector and also stores the position of given Shape
 */
struct Shape
{
    std::vector<Pair> shapeV_;
    ImVec2 pos_;
    int level_;

    inline int equalPixels(Shape shape2){
        assert(shapeV_.size() == shape2.shapeV_.size());
        int resultX1 = 0;
        int resultY1 = 0;
        int resultX2 = 0;
        int resultY2 = 0;
        int result = 0;
        for (size_t i = 0; i < shapeV_.size(); i++)
        {
            resultX1 = shapeV_[i].x_ + pos_.x;
            resultY1 = shapeV_[i].y_ + pos_.y;
            for (size_t j = 0; j < shape2.shapeV_.size(); j++)
            {
                resultX2 = shape2.shapeV_[j].x_ + shape2.pos_.x;
                resultY2 = shape2.shapeV_[j].y_ + shape2.pos_.y;

                if(resultX1 == resultX2 && resultY1 == resultY2)
                {
                    result++;
                }
            }
            
            // if(result > 2)
            //     return result;
        }
        return result;
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
     * Adds a Black Square on given Coordinates x, y
     */
    void addSqr(const int x, const int y, const int level)
    {
        ImVec2 pos(x * grid_step_, y * grid_step_);
        switch (level)
        {
        case 1:
            drw->AddRectFilled(canvas_p0_ + pos, canvas_p0_ + pos + ImVec2(grid_step_, grid_step_), IM_COL32(255, 0, 0, 255));
            break;
        case 2:
            drw->AddRectFilled(canvas_p0_ + pos, canvas_p0_ + pos + ImVec2(grid_step_, grid_step_), IM_COL32(0, 255, 0, 255));
            break;
        case 3:
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
            for (auto pixel : s.shapeV_)
            {
                addSqr(pixel.x_ + pos.x, pixel.y_ + pos.y);
            }
            break;
        default:
            for (auto pixel : s.shapeV_)
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
        Shape sq = {{{0, 0}, {1, 0}, {0, 1}, {1, 1}}, {1, 1}, 0};

        //Create Rectangular Shape in coordinates 0, 0
        Shape rectangle = {{{0, 0}, {1, 0}, {0, 1}, {1, 1}, {0, 2}, {1, 2}}, {0, 0}, 0};
        Shape rectangle1 = {{{0, 0}, {1, 0}, {0, 1}, {1, 1}, {0, 2}, {1, 2}}, {4, 4}, 0};
        Shape rectangle2 = {{{0, 0}, {1, 0}, {0, 1}, {1, 1}, {0, 2}, {1, 2}}, {6, 4}, 0};
        Shape rectangle3 = {{{0, 0}, {1, 0}, {0, 1}, {1, 1}, {0, 2}, {1, 2}}, {1, 1}, 0};
        //TODO shape4 not working 
        Shape rectangle4 = {{{0, 0}, {1, 0}, {0, 1}, {1, 1}, {0, 2}, {1, 2}}, {1, 3}, 0};

        //TODO
        //Push this outside run loop??
        static std::vector<Shape> shapes;
        static std::vector<Shape> shapes1;
        shapes.push_back(rectangle);
        shapes.push_back(rectangle1);
        // shapes1.push_back(rectangle2);
        // shapes1.push_back(rectangle3);
        shapes.push_back(rectangle2);
        shapes.push_back(rectangle3);
        shapes.push_back(rectangle4);
        // std::cout << "equal pix: " << rectangle1.equalPixels(rectangle2) << std::endl;

        /**
         * Comparing the 2 Shape vectors to see how many pixels are equal on each vector
         */ 
        int result = 0;
        std::cout << shapes.size() << std::endl;
        for (size_t i = 0; i < shapes.size() - 1; i++)
        {
            dr.addShape(shapes[i]);
            std::cout << "shapes[" << i << "] level: " << shapes[i].level_ << std::endl;
            result = shapes[i].equalPixels(shapes[i + 1]);
            if (result > 1)
            {
                std::cout << "shape " << i << " and " << i+1 << std::endl;
                if (shapes[i].level_ == shapes[i + 1].level_)
                {
                    shapes[i].level_++;
                    std::cout << "level " << shapes[i+1].level_ << std::endl;
                    std::cout << "shapes[" << i << "] level: " << shapes[i].level_ <<  " AFTER" << std::endl;
                }
                else if (shapes[i].level_ > shapes[i + 1].level_)
                {
                    shapes[i].level_ = shapes[i].level_ + 1;
                }
                
            }
            dr.addShape(shapes[i]);
        }
        result = shapes[shapes.size() - 1].equalPixels(shapes[shapes.size() - 2]);
        if (result > 1)
        {
                if (shapes[shapes.size() - 1].level_ == shapes[shapes.size() - 2].level_)
                {
                    shapes[shapes.size() - 1].level_++;
                }
                else if (shapes[shapes.size() - 2].level_ > shapes[shapes.size() - 1].level_)
                {
                    shapes[shapes.size() - 1].level_ = shapes[shapes.size() - 2].level_ + 1;
                }
                
            dr.addShape(shapes[shapes.size() - 1]);
        }
        
        // for (size_t i = 0; i < shapes.size(); i++)
        // {
        //     dr.addShape(shapes[i]);
        //     for (size_t j = 0; j < shapes1.size(); j++)
        //     {
        //         result = shapes[i].equalPixels(shapes1[j]);
        //         if (result >= 2)
        //         {
        //             //TODO
        //             //What way would be the correct to implement this?
        //             // std::cout<< "need new level"<<std::endl;
        //             shapes1[j].level_ = shapes[i].level_ + 1;
        //             std::cout<< shapes1[j].level_ << std::endl;
        //         }
        //         dr.addShape(shapes1[j]);
        //     }
        // }


        //Draw Rectangular Shape
        // dr.addShape(rectangle);
        // dr.addShape(rectangle1);
        // dr.addShape(rectangle2);
        std::cout << "fdsafdsa" <<rectangle3.level_ << std::endl;
        // dr.addShape(rectangle3);
        

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

        /**
         * Pop all the shapes so Size remains true
         */ 
        for(auto shape : shapes)
        {
            shapes.pop_back();
        }
        for(auto shape : shapes1)
        {
            shapes1.pop_back();
        }
    }

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}
