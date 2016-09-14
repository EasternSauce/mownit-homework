file="plot_ls.jpg"
data="output.txt"
ls="ls.txt"

jpeg(file)

mydata = read.csv(data)
myls = read.csv(ls)

mydata
myls

x = seq(0, 30, 0.1)
y = myls$c0 + myls$c1 * x


plot(mydata$iter, mydata$root, type="p", xlab="iter", ylab="root")
lines(x, y, type="l") 
