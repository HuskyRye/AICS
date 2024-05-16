# 设置仿真环境路径
set sim_home D:/pe_exp_student/sim

# 在当前目录下创建一个叫做 work 的目录， 在里面存放仿真数据文件
vlib ${sim_home}/work

# 将 work 目录下的数据文件映射为一个叫做 work 的仿真库
vmap work ${sim_home}/work

# 编译 compile.f 文件中指定的代码
vlog -f ${sim_home}/compile_0.f

