file="plot.jpg"
rootfile="root.txt"

jpeg(file)

myroot = read.csv(rootfile)

x = seq(0,5,0.01);
y = x^2-5;
zeroes = 0 * x;


plot(x, y, type="l", xaxs="i", xlab="x", ylab="y", col="red", axes=TRUE)
axis(3, myroot$root, col = "violet")
lines(x, zeroes, type="l") 
