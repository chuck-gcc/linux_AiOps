import json
import threading

# {
#   "timestamp": "2025-11-22T04:09:07.416149+01:00",
#   "host": "cc-MS-7B78",
#   "process": "dbus-daemon",
#   "pid": 1042,
#   "facility": "system",
#   "severity": "error",
#   "event_type": "service_timeout",
#   "service": "org.bluez",
#   "message": "Failed to activate service 'org.bluez': timed out (service_start_timeout=25000ms)",
#   "prev_hash":""
# }

class Log_dpkg():
    date: str
    hour: str
    

class Log():
    file: str
    timestamp:str
    host:str
    process: str
    pid: str
    facility: str
    event_type: str
    service: str
    message: str
    prev_hash: str
    
    def toJson(self):
        return json.dumps(
            self, default=lambda o: o.__dict__, 
            indent=4
        )
    
def get_json_log(log: str) -> Log :
    split = log.split(" ", 4)
    # for data in split:
    #     print(data)
    obj = Log()
    obj.file = split[0];
    obj.timestamp = split[1];
    obj.host = split[2];
    start = split[2].find("[") + 1
    end = split[2].find("]")
    obj.process = split[3][0:start - 1]
    obj.pid = split[3][start:end];
    obj.message = split[4]
    obj.event_type = ""
    obj.facility = ""
    obj.prev_hash = ""

    return(obj)

def thread_log(log):

    log: Log = get_json_log(log);

    print(log.toJson())