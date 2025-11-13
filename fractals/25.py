import turtle

def draw_snowflake(x, y, size, t, color, width):

    original_heading = t.heading()
    
    t.penup()
    t.goto(x, y)
    t.setheading(90)
    t.color(color)
    t.pensize(width)
    t.pendown()
    
    for _ in range(5):
        t.forward(size)
        t.backward(size)
        t.right(72)
    
    t.setheading(original_heading)

def draw_beautiful_snowflake():
    screen = turtle.Screen()
    screen.setup(1200, 800)  
    screen.bgcolor("midnightblue")  
    
    t = turtle.Turtle()
    t.speed(0)  
    t.hideturtle()

    colors = ["#1E3A8A", "#3B82F6", "#60A5FA", "#93C5FD", "#DBEAFE"]

    base_size = 120
    levels = 5

    current_points = [(0, 0, base_size)]
    
    for level in range(levels):
        new_points = []
        color = colors[level]
        width = 4 - level 
        
        for x, y, size in current_points:
            draw_snowflake(x, y, size, t, color, width)
            
            if level < levels - 1:
                t.penup()
                t.goto(x, y)
                t.setheading(90)
                t.pendown()
                
                for i in range(5):
                    t.forward(size)
                    next_x, next_y = t.xcor(), t.ycor()
                    next_size = size / 2.56
                    new_points.append((next_x, next_y, next_size))
                    t.backward(size)
                    t.right(72)
        
        current_points = new_points
    
    turtle.done()

draw_beautiful_snowflake()