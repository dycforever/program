// 加载File System读写模块  
var fs = require('fs');  
// 加载编码转换模块  
// var iconv = require('iconv-lite');   
  
var file = "node.out";  
for (;;) {
    writeFile(file);  
}
// readFile(file);  
  

function writeFile(file){  
    // 测试用的中文  
    var str = "\r\n我是一个人Hello myself!" * 10;  
    // 把中文转换成字节数组  
    // var arr = iconv.encode(str, 'gbk');  
    var arr = str;
//    console.log(arr);  
      
    // appendFile，如果文件不存在，会自动创建新文件  
    // 如果用writeFile，那么会删除旧文件，直接写新文件  
    fs.appendFile(file, arr, function(err){  
        if(err)  
            console.log("fail " + err);  
    });  
}  
  
function readFile(file){  
    fs.readFile(file, function(err, data){  
        if(err)  
            console.log("读取文件fail " + err);  
        else{  
            // 读取成功时  
            // 输出字节数组  
            console.log(data);  
            // 把数组转换为gbk中文  
            // var str = iconv.decode(data, 'gbk');  
            console.log(data);  
        }  
    });  
} 

