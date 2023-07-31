cmd_/home/roee/Documents/checkpoint/modules.order := {   echo /home/roee/Documents/checkpoint/hello_checkpoint_module.ko; :; } | awk '!x[$$0]++' - > /home/roee/Documents/checkpoint/modules.order
