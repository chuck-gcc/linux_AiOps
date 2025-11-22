LINUX_SERVER_NAME=iagent
GCOM=""
LINUX_SERVER_PATH = $(PWD)/linux_log_agent 
LOG_FILE= /var/log/auth.log /var/log/kern.log

.PHONY: ls

lsrun:
	cd $(LINUX_SERVER_PATH) && cmake -B build . && cmake --build build && ./build/srcs/iagent $(LOG_FILE)

lsclean:
	cd $(LINUX_SERVER_PATH) && rm -rf build

lsre: lsclean lsrun

psrun:
	python3 ./python_serveur/main.py

git:
	git add . && git commit -m $(GCOM) && git push origin main