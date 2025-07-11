// main.js
alert('Hello from external script!');
const externalTitle = document.getElementById('external-title');
if (externalTitle) {
    externalTitle.textContent = "外部脚本修改标题";
}

// 等待DOM加载完成
document.addEventListener('DOMContentLoaded', function() {
    // 获取DOM元素
    const button = document.getElementById('myButton');
    const output = document.getElementById('output');

    // 添加事件监听器
    button.addEventListener('click', function() {
        output.textContent = '按钮被点击了！';
    });
});