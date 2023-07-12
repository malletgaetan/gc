# gc
Norminette ready Garbage Collector library for 42 projects

## Examples

#### Initialization
```C
t_gcan  gc;
gc_init(&gc);
```

#### Allocate memory
```C
ptr = gc_malloc(&gc, sizeof(struct mystruct));
```

#### Free memory
```C
// before => ptr != NULL
gc_free(&gc, (void **)&ptr);
// after => ptr == NULL
```
#### Free all tracked memory
```C
gc_clean(&gc);
```
