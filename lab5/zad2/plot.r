file="plot33.pdf"


results = read.csv("data.txt")
results = results[results$alg=="a3",]
results

pdf(file, height=4, width=4, bg="white")

plot(results$a, results$n, type="l", xlab="n", ylab="przedziały", col="red")
title("qawo")

