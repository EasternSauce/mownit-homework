results1 = read.csv("gslinterp1.txt")
results2 = read.csv("gslinterp2.txt")
results3 = read.csv("gslinterp3.txt")

options(scipen=999)

pdf(file="czasygsl.pdf", height=4, width=4, bg="white")

plot(results1$n, results1$time/1000, type="l", xlab="number of nodes", ylab="computation time (miliseconds)", col="red")
lines(results2$n, results2$time/1000, col="green")
lines(results3$n, results3$time/1000, col="blue")
legend("topleft", c("polynomial","cspline","akima"),lty=c(1,1,1,1),lwd=c(2.5,2.5,2.5,2.5),col=c("red","green","blue"), cex=0.5)
title("Time in relation to number of nodes")

dev.off()

