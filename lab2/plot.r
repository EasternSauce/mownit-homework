results = read.csv("blas1.txt")

options(scipen=999)

pdf(file="blas1.pdf", height=4, width=4, bg="white")

plot(results$time/1000000~results$vsize, type="o", lty=1, xlab="Size of vector/matrix", ylab="Time in seconds", col="blue")

results = read.csv("blas2.txt")

options(scipen=999)

pdf(file="blas2.pdf", height=4, width=4, bg="white")

plot(results$time/1000000~results$vsize, type="o", lty=1, xlab="Size of vector/matrix", ylab="Time in seconds", col="blue")

results = read.csv("blas3.txt")

options(scipen=999)

pdf(file="blas3.pdf", height=4, width=4, bg="white")

plot(results$time/1000000~results$vsize, type="o", lty=1, xlab="Size of vector/matrix", ylab="Time in seconds", col="blue")


dev.off()
