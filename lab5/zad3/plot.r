file="plot111.pdf"

pdf(file, height=4, width=4, bg="white")

x = seq(-20,20,0.01);
y = 1/(x^2+4);

plot(x, y, type="l", xlab="x", ylab="y", col="red")
title("y=1/(x^2+4)")

