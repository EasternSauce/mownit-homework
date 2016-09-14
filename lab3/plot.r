results = read.csv("lu.txt")

options(scipen=999)

pdf(file="lu.pdf", height=4, width=4, bg="white")

plot(results$time/1000000~results$size, type="o", lty=1, xlab="Size of vector/matrix", ylab="Time in seconds", col="blue")

results = read.csv("tridiag.txt")

options(scipen=999)

pdf(file="tridiag.pdf", height=4, width=4, bg="white")

plot(results$time~results$size, type="o", lty=1, xlab="Size of vector/matrix", ylab="Time in microseconds", col="blue")

dev.off()
