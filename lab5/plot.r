file="plot3.pdf"

pdf(file, height=4, width=4, bg="white")

x = seq(0,20,0.01);
y = 3*cos(3*x);

plot(x, y, type="l", xlab="x", ylab="y", col="red")
title("y=3cos(3x)")

