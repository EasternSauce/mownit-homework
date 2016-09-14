results1 = read.csv("tinterp1.txt")
results2 = read.csv("tinterp2.txt")
results3 = read.csv("tinterp3.txt")

options(scipen=999)

pdf(file="czasy.pdf", height=4, width=4, bg="white")

plot(results1$n, results1$time/1000000, type="l", xlab="number of nodes", ylab="computation time (seconds)", col="red", ylim=c(0, 1))
lines(results2$n, results2$time/1000000, col="green")
lines(results3$n, results3$time/1000000, col="blue")
legend("topleft", c("GSL","Lagrange","Newton"),lty=c(1,1,1,1),lwd=c(2.5,2.5,2.5,2.5),col=c("red","green","blue"), cex=0.5)
title("Time in relation to number of nodes")

dev.off()

