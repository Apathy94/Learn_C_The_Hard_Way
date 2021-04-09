#ifndef _object_h   // 如果没有定义
#define _object_h

typedef enum
{
    NORTH, SOUTH, EAST, WEST
} Direction;

typedef struct
{
    char *description;
    int (*init)(void *self);
    void (*describe)(void *self);
    void (*destroy)(void *self);
    void *(*move)(void *self, Direction direction);
    int (*attack)(void *self, int damage);
} Object;

int Object_init(void *self);
void Object_destroy(void *self);
void Object_describe(void *self);
void *Object_move(void *self, Direction direction);
int Object_attack(void *self, int damage);
void *Object_new(size_t size, Object proto, char *description);

/*这条语句创建了一个宏，就像模板函数一样，无论你在哪里编写左边的代码，都会展开成右边的代码。这条语句
 *仅仅是对我们通常调用的Object_new制作了一个快捷方式，并且避免了潜在的调用错误。在宏这种工作方式下，
 *T、N还有New都被“注入”进了右边的代码中。T##Proto语法表示“将Proto连接到T的末尾”，所以如果你写下NEW(
 * Room, "Hello.")，就会在这里变成RoomProto。
*/
#define NEW(T, N) Object_new(sizeof(T), T##Proto, N)
#define _(N) proto.N

#endif
