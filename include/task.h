#define MAX_INPUT_CHAR 1600

typedef enum {
  NONE,
  SEND_EMAIL,
  FILE_PAPERWORK,
  DATA_ENTRY,
  CLEANING,
  DELIVER
} Task;

void startTask(Task taskGiven);
void finishTask();

void drawTasks();

void updateTasks();
void initTasks();
void cleanTasks();
