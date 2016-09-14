results1 = read.csv("inter1.txt")
results2 = read.csv("inter2.txt")
results3 = read.csv("inter3.txt")

options(scipen=999)

pdf(file="wykres.pdf", height=4, width=4, bg="white")

plot(results1$x, results1$y, type="l", xlab="x", ylab="y", col="red")
lines(results2$x, results2$y, col="green")
lines(results3$x, results3$y, col="blue")
legend("topleft", c("GSL","Lagrange","Newton"),lty=c(1,1,1,1),lwd=c(2.5,2.5,2.5,2.5),col=c("red","green","blue"), cex=0.5)
title("Interpolations of f(x) = x + 0.5 * sin (x)")

dev.off()

