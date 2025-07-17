#!/usr/bin/env python3
import argparse
import os
import sys
import subprocess


def run_test(lab_name):
    """运行指定实验的测试"""
    lab_path = os.path.join('labs', lab_name)
    
    # 检查实验目录是否存在
    if not os.path.exists(lab_path):
        print(f"错误: 找不到实验 '{lab_name}'")
        print(f"实验目录应该位于 {lab_path}")
        return False
    
    # 首先检查框架目录结构 labs/<lab_name>/framework/autograder
    framework_autograder_path = os.path.join(lab_path, 'framework', 'autograder')
    
    # 然后检查直接的autograder目录 labs/<lab_name>/autograder
    direct_autograder_path = os.path.join(lab_path, 'autograder')
    
    # 确定要使用的autograder路径
    if os.path.exists(framework_autograder_path):
        autograder_path = framework_autograder_path
        autograder_rel_path = 'framework/autograder/autograder.py'
    elif os.path.exists(direct_autograder_path):
        autograder_path = direct_autograder_path
        autograder_rel_path = 'autograder/autograder.py'
    else:
        print(f"错误: 实验 '{lab_name}' 不包含autograder目录")
        print(f"autograder目录应该位于 {framework_autograder_path} 或 {direct_autograder_path}")
        return False
    
    autograder_script = os.path.join(autograder_path, 'autograder.py')
    if not os.path.exists(autograder_script):
        print(f"错误: 找不到autograder.py脚本")
        print(f"该脚本应该位于 {autograder_script}")
        return False
    
    print(f"正在运行 '{lab_name}' 的测试...")
    try:
        # 确保在实验目录中运行autograder
        os.chdir(lab_path)
        result = subprocess.run([sys.executable, autograder_rel_path], check=True)
        os.chdir('../..')  # 回到原来的目录
        return result.returncode == 0
    except subprocess.CalledProcessError as e:
        print(f"测试运行失败，返回代码: {e.returncode}")
        os.chdir('../..')  # 确保回到原来的目录
        return False


def list_labs():
    """列出所有可用的实验"""
    if not os.path.exists('labs'):
        print("错误: 找不到labs目录")
        return []
    
    labs = []
    for item in os.listdir('labs'):
        lab_path = os.path.join('labs', item)
        if os.path.isdir(lab_path):
            # 检查两种可能的autograder目录结构
            if (os.path.exists(os.path.join(lab_path, 'framework', 'autograder')) or 
                os.path.exists(os.path.join(lab_path, 'autograder'))):
                labs.append(item)
    
    return labs


def convert_config(lab_name, encrypt=False, key=None):
    """将实验的YAML配置转换为Python字节码"""
    lab_path = os.path.join('labs', lab_name)
    
    # 检查两种可能的autograder路径
    framework_autograder_path = os.path.join(lab_path, 'framework', 'autograder')
    direct_autograder_path = os.path.join(lab_path, 'autograder')
    
    if os.path.exists(framework_autograder_path):
        autograder_path = framework_autograder_path
    elif os.path.exists(direct_autograder_path):
        autograder_path = direct_autograder_path
    else:
        print(f"错误: 找不到autograder目录")
        return False
    
    yaml_config = os.path.join(autograder_path, 'test_config.yaml')
    
    if not os.path.exists(yaml_config):
        print(f"错误: 找不到配置文件 '{yaml_config}'")
        return False
    
    # 首先检查autograder目录下是否有yaml_to_pyc.py脚本
    yaml_to_pyc_path = os.path.join(autograder_path, 'yaml_to_pyc.py')
    if os.path.exists(yaml_to_pyc_path):
        yaml_to_pyc_script = yaml_to_pyc_path
    elif os.path.exists('yaml_to_pyc.py'):
        yaml_to_pyc_script = 'yaml_to_pyc.py'
    else:
        print("错误: 找不到yaml_to_pyc.py脚本")
        return False
    
    # 构建命令
    cmd = [sys.executable, yaml_to_pyc_script, yaml_config, '--output', 
           os.path.join(autograder_path, 'test_config')]
    
    if encrypt:
        cmd.append('--encrypt')
        if key:
            cmd.extend(['--key', key])
    
    print(f"正在转换 '{lab_name}' 的配置文件...")
    try:
        result = subprocess.run(cmd, check=True)
        return result.returncode == 0
    except subprocess.CalledProcessError as e:
        print(f"配置转换失败，返回代码: {e.returncode}")
        return False


def main():
    parser = argparse.ArgumentParser(description="实验自动测试工具")
    subparsers = parser.add_subparsers(dest='command', help='命令')
    
    # 测试命令
    test_parser = subparsers.add_parser('test', help='运行指定实验的测试')
    test_parser.add_argument('lab', help='要测试的实验名称')
    
    # 列出所有实验的命令
    list_parser = subparsers.add_parser('list', help='列出所有可用的实验')
    
    # 添加新命令：转换配置
    convert_parser = subparsers.add_parser('convert', help='将实验的YAML配置转换为Python字节码')
    convert_parser.add_argument('lab', help='要转换配置的实验名称')
    convert_parser.add_argument('--encrypt', action='store_true', help='加密配置数据')
    convert_parser.add_argument('--key', help='指定加密密钥')
    
    args = parser.parse_args()
    
    if args.command == 'test':
        success = run_test(args.lab)
        sys.exit(0 if success else 1)
    elif args.command == 'list':
        labs = list_labs()
        if labs:
            print("可用的实验:")
            for lab in labs:
                print(f"  - {lab}")
        else:
            print("没有找到可用的实验")
    elif args.command == 'convert':
        success = convert_config(args.lab, args.encrypt, args.key)
        sys.exit(0 if success else 1)
    else:
        parser.print_help()


if __name__ == "__main__":
    main() 