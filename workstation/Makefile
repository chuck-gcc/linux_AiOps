# This Makefile is used on gpu server for the docker and llama automatisations.


#Docker parametres in gpu server

# ressources: https://rocm.docs.amd.com/projects/install-on-linux/en/latest/install/3rd-party/llama-cpp-install.html

DOCK_NAME=tresa_llamacpp
DOCK_IMAGE=llama_op:latest
DOCK_PARAM=-itd

REMOVE=
NAME=--name=$(DOCK_NAME)
WORKDIR=-w /home/llama/llama.cpp
DEVICE_1=--device=/dev/kfd
DEVICE_2=--device=/dev/dri
GROUP=--group-add video 
CAP=--cap-add=SYS_PTRACE
SECURITY=--security-opt
COMP=seccomp=unconfined
IPC=--ipc=host
PRIV=--privileged
PORT1=-p 2222:22
PORT2=-p 8080:8080
VOLUME=-v /media:/data
INIT=--init 
.PHONY: dstop drm drun dstart re bash

dstop:
	docker stop $(DOCK_NAME)
	@echo $(DOCK_NAME) stopped

drm: dstop
	docker rm -f $(DOCK_NAME)
	@echo $(DOCK_NAME) removed
	
drun:
	docker run $(DOCK_PARAM) $(REMOVE) $(NAME) $(INIT) $(WORKDIR) $(PRIV) $(DEVICE_1) $(DEVICE_2) $(GROUP) $(CAP) $(SECURITY) $(COMP) $(IPC) $(PORT1) $(PORT2) $(VOLUME) $(DOCK_IMAGE)
	@echo $(DOCK_NAME) is now running

dstart: drun
	docker exec -itd $(DOCK_NAME)  /usr/sbin/sshd
	@echo SSHD in $(DOCK_NAME) is now running

re: drm dstart

git:
	docker commit $(DOCK_NAME) $(DOCK_IMAGE)


bash:
	docker exec -it $(DOCK_NAME)  bash

#llama-server parametres in gpu server

#ressources: https://github.com/ggml-org/llama.cpp/tree/master/tools/server


SERVER_PATH=./build/bin/llama-server
NGL=-ngl 99
OFFLINE=--offline
FLASH_ATT=--flash-attn 1
CONTEXT=--context-shift
CONTEXT_SIZE= -c 4096
#Modeles Path
GPTOSS=-m /data/models/gguf_models/gpt-oss-20b-GGUF/gpt-oss-20b-F16.gguf

QVL8I=-m /data/models/gguf_models/Qwen3-VL-8B-Instruct-GGUF/Qwen3VL-8B-Instruct-F16.gguf 
QVL8IMM=--mmproj /data/models/gguf_models/Qwen3-VL-8B-Instruct-GGUF/mmproj-Qwen3VL-8B-Instruct-F16.gguf

QVL8T=-m /data/models/gguf_models/Qwen3-VL-8B-Thinking-GGUF/Qwen3VL-8B-Thinking-F16.gguf 
QVL8TMM=-m /data/models/gguf_models/Qwen3-VL-8B-Thinking-GGUF/mmproj-Qwen3VL-8B-Thinking-F16.gguf

QVL32I=-m /data/models/gguf_models/Qwen3-VL-32B-Instruct-GGUF/Qwen3VL-32B-Instruct-F16-merged.gguf 
QVL32IMM=-m /data/models/gguf_models/Qwen3-VL-32B-Instruct-GGUF/mmproj-Qwen3VL-32B-Instruct-F16.gguf 

QC30=-m /data/models/gguf_models/Qwen3-Coder-30B-A3B-Instruct-GGUF/Qwen3-Coder-30B-A3B-Instruct-UD-Q8_K_XL.gguf 



# gpt-oss 20B
gpt:
	docker exec -itd  $(DOCK_NAME)  $(SERVER_PATH) $(NGL) $(FLASH_ATT)  $(GPTOSS) $(OFFLINE)
	@echo gpt-oss 20B is now runnig on 127.0.0.1:8080

# qwen3 VL 8B Instruct
q8i:
	docker exec -it  $(DOCK_NAME)  $(SERVER_PATH) $(NGL) $(FLASH_ATT) $(QVL8I) $(QVL8IMM) $(OFFLINE)
	@echo qwen3 VL 8B Instruct is now runnig on 127.0.0.1:8080
# qwen3 VL 8B Thinking
q8t:
	docker exec -itd  $(DOCK_NAME)  $(SERVER_PATH) $(NGL) $(FLASH_ATT) $(QVL8T) $(QVL8TMM) $(OFFLINE)
	@echo qwen3 VL 8B Thinking is now runnig on 127.0.0.1:8080

# qwen3 VL 32B Instruct
q32i:
	docker exec -itd  $(DOCK_NAME)  $(SERVER_PATH) $(NGL) $(FLASH_ATT) $(QVL32I) $(QVL32IMM) $(OFFLINE)
	@echo qwen3 VL 32B Instruct is now runnig on 127.0.0.1:8080

# qwen3 Coder 30b
q30c:
	docker exec -itd  $(DOCK_NAME)  $(SERVER_PATH) $(NGL) $(FLASH_ATT) $(QC30) $(OFFLINE)

llmstop:
	docker exec -it $(DOCK_NAME)  bash -c 'kill -9 $$(pidof llama-server)'
	@echo llama server is off


llm: dstart q30c
