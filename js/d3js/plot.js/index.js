var width = 500, height = 250, margin = {left:50, top:30, right:20,bottom:20},
g_width = width - margin.left - margin.right,
g_height = height - margin.top - margin.bottom;

//获取div，向里面添加svg
var svg = d3.select("#container")
.append("svg:svg")//在“container”中插入svg
.attr("width", width)//设置svg的宽度
.attr("height", height)//设置svg的高度

//添加g元素
var g = d3.select("svg")
.append("g")
.attr("transform","translate("+margin.left+","+margin.top+")")

var data = [1,3,5,9,4,2,3,6,8]//定义一个数组，里面放置了一些任意数字
var scale_x = d3.scale.linear()//把曲线沿x轴按比例放大
.domain([0, data.length-1])
.range([0, g_width])
var scale_y = d3.scale.linear()//把曲线沿y轴按比例放大
.domain([0, d3.max(data)])
.range([0, g_height])


var line_generator = d3.svg.line()//d3中绘制曲线的函数
.x(function(d, i){return scale_x(i);})//曲线中x的值
.y(function(d){return scale_y(d);})//曲线中y的值
.interpolate("cardinal")//把曲线设置光滑

d3.select("g")
.append("path")
.attr("d", line_generator(data))
