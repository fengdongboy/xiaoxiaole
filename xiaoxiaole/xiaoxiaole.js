
// ������
// 1�������̣߳���Ϊ�߳����첽�ģ��� �Զ���� ������ʼ
// 2�������ͼȨ�ޣ�������֣�
// 3�����н�ͼ
 
// 1�������̣߳��ҵ����������ʼ�����Ҵ����¼���ֻ��Ҫִ��һ�ξͿ��ԣ�
threads.start(function () {
    var beginBtn;
    if (beginBtn = classNameContains("Button").textContains("������ʼ").findOne(2000)) {
        beginBtn.click();
    }
});
        

// 2�������ͼ
if(!requestScreenCapture()){
    toast("�����ͼʧ��");
    exit();
}

// ��ͼ
let img = captureScreen();
// �ҶȻ�ͼƬ
let gray = images.grayscale(img);



// 3�����н�ͼ
captureScreen("/sdcard/img.png");


