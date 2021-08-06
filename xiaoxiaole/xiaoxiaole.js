
// 三步走
// 1、开启线程（因为线程是异步的）， 自动点击 立即开始
// 2、请求截图权限（弹框出现）
// 3、进行截图
 
// 1、开启线程，找到点击立即开始，并且触发事件（只需要执行一次就可以）
threads.start(function () {
    var beginBtn;
    if (beginBtn = classNameContains("Button").textContains("立即开始").findOne(2000)) {
        beginBtn.click();
    }
});
        

// 2、请求截图
if(!requestScreenCapture()){
    toast("请求截图失败");
    exit();
}

// 截图
let img = captureScreen();
// 灰度化图片
let gray = images.grayscale(img);



// 3、进行截图
captureScreen("/sdcard/img.png");


