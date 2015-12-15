#include <string>
#include <map>
#include <iostream>
#include <assert.h>

struct vertex;
struct edge {
    size_t beg;
    size_t lim;
    vertex *end;
    edge():beg(0),lim(0),end(0){};
};
struct vertex {
    std::map <char,edge> child;
    size_t id_dontuse;
    size_t depth_dontuse;
    vertex *suffix_link;
};

#define min(x,y) ((x<y)?(x):(y))

void print_edge(size_t shift, std::string &s, edge *e) {
    size_t lim;

    // Выводим отсутп
    for (size_t i = 0; i < shift; i++) printf(" ");
    // Выводим текст ребра
    if (e->end) lim = e->lim;
    else lim = s.length();
    //
    for (size_t i = e->beg; i < lim; i++)
        printf("%c", s[i]);
    // Если есть концевая вершина, выводим дочерние рёбра...
    if (e->end) {
        // Концевая вершина есть...
        printf("(depth:%d;id:%d;link:%d)\n", (int) e->end->depth_dontuse, (int) e->end->id_dontuse,
               (int) (e->end->suffix_link ? (e->end->suffix_link->id_dontuse) : (size_t) -1));
        //
        for(auto ch = e->end->child.begin(); ch != e->end->child.end(); ++ch)
            print_edge(shift + lim - e->beg, s, &(ch->second));
    }
    else {
        // Концевой вершины нет - выводим $...
        printf("$\n");
    }
}

int main(void) {
    std::string s;
    vertex root;
    edge edge_to_root;
    size_t cur_suf;
    size_t cur_suf_pos;
    edge *cur_edge;
    size_t cur_edge_pos;
    size_t vertex_id = 0;
    size_t depth; // Текущая глубина
    vertex *no_link_vertex; // Последняя созданная вершина (у которой ещё нет стрелки)
    size_t  no_link_depth;  // И её глубина
    size_t ops = 0; //Подсчёт итераций цикла
    vertex *last_linked_vertex;
    size_t  last_linked_depth;
    edge fictive_edge;

  s = "abababaab"; //"ojojojojojoj"
  s =  "ojojaojojb";

    printf("%s\n", s.c_str());

    cur_suf = cur_suf_pos = 0;
    cur_edge = &edge_to_root;
    edge_to_root.end = &root;
    root.id_dontuse = 0;
    root.depth_dontuse = 0;
    root.suffix_link = 0;
    cur_edge_pos = 0;
    depth = 0;
    no_link_vertex = 0;
    no_link_depth = (size_t) - 1;
    last_linked_vertex = 0;
    last_linked_depth  = (size_t) -1;


    for (size_t len = 1; len <= s.length(); len++) {
        while (cur_suf_pos < len) {
            char ch = s[cur_suf_pos];
            ops++;
            if (cur_edge_pos < cur_edge->lim) {
                // Стоим на ребре...
                if (no_link_vertex) {
                    size_t jump;
                    jump = min(
                            no_link_depth - 1 - depth,        // ограничение по глубине
                            cur_edge->lim - cur_edge_pos);  // ограничение по ребру
                    if (jump) {
                        cur_suf_pos += jump;
                        cur_edge_pos += jump;
                        depth += jump;
                        continue;
                    }
                }
                if (ch == s[cur_edge_pos]) {
                    // очередные символы совпадают - делаем шаг
                    // как по ребру, так и по суффиксу...
                    cur_suf_pos++;
                    cur_edge_pos++;
                    depth++;
                    continue;
                }
                // Стоим на ребре, но очередные символы не совпадают
                // Разрезаем ребро, создавая новую вершину
                vertex *nv = new vertex;
                // Инициализация единственного исходящего ребра из
                // новой вершины
                nv->child[s[cur_edge_pos]].beg = cur_edge_pos;
                nv->child[s[cur_edge_pos]].lim = cur_edge->lim;
                nv->child[s[cur_edge_pos]].end = cur_edge->end;
                nv->id_dontuse = ++vertex_id;
                nv->depth_dontuse = depth;
                nv->suffix_link = 0;
                // Укорачиваем старое рабро
                cur_edge->lim = cur_edge_pos;
                cur_edge->end = nv;

                if (no_link_vertex) {
                    assert(no_link_depth == depth + 1);
                    no_link_vertex->suffix_link = nv;
                }

                no_link_vertex = nv;
                no_link_depth  = depth;
            }
            // Попав сюда, мы стоим в концевой вершине ребра
            if (cur_edge->end->suffix_link) {
                last_linked_vertex = cur_edge->end;
                last_linked_depth  = depth;
            }
            if (no_link_vertex && (no_link_depth == depth+1)) {
                no_link_vertex->suffix_link = cur_edge->end;

                no_link_vertex = 0;
                no_link_depth  = (size_t) -1;
            }

            cur_edge = &(cur_edge->end->child[ch]);
            if (cur_edge->lim) {
                // Встали на существующее ребро...
                cur_edge_pos = cur_edge->beg;
                continue;
            } else {
                // Создали новое ребро...
                cur_edge->beg = cur_suf_pos;
                cur_edge->lim = (size_t)(-1); // бесконечность
                cur_edge->end = 0;

                // Текущий суффикс получил свой лист, переходим
                // к следующему суффиксу...
                cur_suf++;
                cur_suf_pos = cur_suf;
                if (last_linked_vertex) {
                    // Прыгаем по суффиксной стрелке к вершине следующего суффикса
                    last_linked_vertex = last_linked_vertex->suffix_link;
                    last_linked_depth --;

                    cur_suf_pos += last_linked_depth;

                    fictive_edge.beg = 0;
                    fictive_edge.lim = 0;
                    fictive_edge.end = last_linked_vertex;

                    cur_edge = &fictive_edge;
                    cur_edge_pos = 0;

                    depth = last_linked_depth;

                    last_linked_vertex = 0;
                    last_linked_depth  = (size_t) -1;
                    continue;
                }
                //Hello
                // Прыгаем в корень дерева...
                cur_edge = &edge_to_root;
                cur_edge_pos = 0;
                depth = 0;
                continue;
            }
        }
    }
    printf("%d\n", (int) ops);

  print_edge(0, s, &edge_to_root);

/*    for (;;)
    {
        std::string p;
        std::cin >> p;
        if (p == std::string("exit")) break;
        find_substring(s, &edge_to_root, p);
    }
*/

    return 0;
}