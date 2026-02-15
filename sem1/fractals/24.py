import turtle

def draw_tree(t, x1, y1, x2, y2, depth, depth_limit, colors):
    if depth == depth_limit:
        return
    
    x_size = x2 - x1
    y_size = y2 - y1
    x3 = x2 - y_size
    y3 = y2 + x_size
    x4 = x1 - y_size
    y4 = y1 + x_size

    color_index = depth % len(colors)
    t.color(colors[color_index])
    
    t.penup()
    t.goto(x1, y1)
    t.pendown()
    
    t.begin_fill()
    t.goto(x2, y2)
    t.goto(x3, y3)
    t.goto(x4, y4)
    t.goto(x1, y1)
    t.end_fill()

    x5 = x4 + 0.5 * (x_size - y_size)
    y5 = y4 + 0.5 * (x_size + y_size)

    draw_tree(t, x4, y4, x5, y5, depth + 1, depth_limit, colors)
    draw_tree(t, x5, y5, x3, y3, depth + 1, depth_limit, colors)

screen = turtle.Screen()
screen.setup(1200, 800)
screen.bgcolor("white")
    
t = turtle.Turtle()
t.speed(0)
t.hideturtle()
t.pensize(1)
depth_limit = 6
colors = ['#d22e6b','#d22e6b', '#2ea9d2', '#2ea9d2', '#26cd38', '#26cd38']

draw_tree(t, -100, -200, 50, -200, 0, depth_limit, colors)
screen.exitonclick()
