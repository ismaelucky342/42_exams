# Examen Level 1 (C++) — Explicación completa

Este examen contiene **tres ejercicios independientes**, típicos de una piscina C++ estilo 42: `vect2`, `bigint` y `polyset`. Los tres giran en torno a las mismas ideas centrales: **sobrecarga de operadores**, **forma canónica ortodoxa** (constructor, copia, asignación, destructor) y, en el caso de `polyset`, **herencia múltiple/virtual**.

---

## 1. `vect2` — Sobrecarga de operadores sobre un vector 2D

### Qué se pide

Crear una clase `vect2` que represente un vector de 2 componentes enteras (`x`, `y`) y que se comporte "como un `int`" en todo lo posible: se pueda sumar, restar, multiplicar por un escalar, incrementar/decrementar (pre y post), negar, comparar, imprimir con `<<` y acceder a sus componentes con `[]`.

El `main.cpp` que te dan es en realidad **el test**: si tu clase está bien hecha, ese código compila y se comporta como indican los comentarios (`// 1, 2`, `// 2, 3`, etc.). No hay que modificar el `main`, solo implementar `vect2.hpp` y `vect2.cpp` para que ese código funcione.

### El `.hpp`: el contrato de la clase

```cpp
class vect2{
    private:
        int v[2];
    public:
        vect2(int x = 0, int y = 0);
        int& operator[](int index);
        const int& operator[](int index) const;
        vect2& operator+=(const vect2 &other);
        ...
};
```

Puntos clave a entender:

- **Un solo constructor con valores por defecto** (`vect2(int x = 0, int y = 0)`) cubre a la vez el constructor por defecto (`vect2 v1;` → `(0,0)`) y el constructor con parámetros (`vect2 v2(1,2);`). No hace falta escribir dos constructores.
- **`operator[]` duplicado**: una versión no-`const` que devuelve `int&` (permite `v1[1] = 12;`, es decir, modificar) y otra versión `const` que devuelve `const int&` (para objetos `const`, como `v3`, que solo se pueden leer). Esto es un patrón muy común en C++: cuando quieres que el operador funcione tanto en objetos modificables como en objetos `const`, defines las dos sobrecargas.
- No se declara copia/asignación/destructor explícitos porque el compilador genera automáticamente unos correctos (la clase solo tiene un array de `int`, no hay memoria dinámica que gestionar). Esto también es parte de "saber cuándo *no* hace falta escribir la forma canónica completa".

### El `.cpp`: la implementación

```cpp
vect2::vect2(int x, int y) { v[0] = x, v[1] = y; }
```
El constructor simplemente guarda `x` e `y` en el array interno.

```cpp
vect2& vect2::operator+=(const vect2& o) { v[0]+=o[0], v[1]+=o[1]; return *this; }
vect2 vect2::operator+(const vect2& o) const { return vect2(*this) += o; }
```
Aquí está el patrón clásico de C++: **implementar `+` en términos de `+=`**. Se crea una copia del objeto actual (`vect2(*this)`), se le aplica `+=` con el otro vector, y se devuelve esa copia. Esto evita duplicar la lógica de la suma y es la forma idiomática de definir operadores compuestos junto a los simples. Lo mismo se repite con `-=`/`-` y `*=`/`*`.

```cpp
vect2& vect2::operator++() { ++v[0], ++v[1]; return *this; }        // pre-incremento
vect2 vect2::operator++(int) { vect2 t(*this); ++(*this); return t; } // post-incremento
```
La diferencia entre pre y post incremento en C++ es puramente de **firma**: `operator++()` sin argumentos es el pre-incremento (`++v4`) y devuelve una referencia al propio objeto ya modificado. `operator++(int)` con un `int` "fantasma" (nunca se usa, solo sirve para distinguir la firma) es el post-incremento (`v4++`): guarda una copia del estado *antes* de modificar, incrementa el objeto real, y devuelve la copia guardada (por valor, no por referencia, porque esa copia es una variable local que desaparece al salir de la función).

```cpp
vect2 vect2::operator-() const { return vect2(-v[0], -v[1]); }
```
El operador unario `-` (un solo argumocamente implícito, `*this`) devuelve un vector nuevo con los signos invertidos. Se distingue del `operator-(const vect2&)` binario por el número de parámetros.

```cpp
bool vect2::operator==(const vect2& o) const { return v[0]==o[0] && v[1]==o[1]; }
bool vect2::operator!=(const vect2& o) const { return !(*this == o); }
```
Otra vez el mismo patrón de reutilización: `!=` se define como la negación de `==`, para no repetir lógica ni arriesgarse a que ambos operadores queden inconsistentes entre sí.

```cpp
vect2 operator*(int s, const vect2& o) { return o * s; }
```
Esta es una **función libre**, no un método de la clase. Es necesaria porque el `main` hace `3 * v2` (escalar primero). Como en una llamada a método el objeto siempre va a la izquierda (`v2 * 3`), la única forma de soportar `escalar * vector` es con una función fuera de la clase que reciba el `int` como primer argumento y simplemente invierta el orden delegando en el `operator*` que sí es miembro de la clase.

```cpp
std::ostream& operator<<(std::ostream& os, const vect2& o) { return os << "{" << o[0] << ", " << o[1] << "}"; }
```
También es una función libre (no puede ser miembro porque el primer operando es `std::ostream`, no un `vect2`). Devuelve la referencia al `ostream` para poder **encadenar** `<<` (`std::cout << v1 << v2`).

### Traza mental del `main.cpp`

Si sigues el `main` paso a paso verás por qué los comentarios dicen esos valores: `v4++` imprime `(2,3)` y **luego** incrementa a `(3,4)`; `++v4` imprime ya `(3,4)`; etc. Es un buen ejercicio repasarlo a mano para confirmar que entiendes pre/post incremento.

---

## 2. `bigint` — Enteros de precisión arbitraria

### Qué se pide

En C++, un `unsigned int` normal tiene un límite (`SIZE_MAX`). Un **bignum** (o *bigint*) es una clase que representa números enteros arbitrariamente grandes sin perder precisión, guardando el número como una **cadena de dígitos** en lugar de un tipo numérico nativo.

Se pide implementar: suma, comparación, y un "desplazamiento de dígitos" (`digitshift`) que funciona como el `<<`/`>>` de bits pero en base 10: `42 << 3 == 42000` (añade 3 ceros) y `1337 >> 2 == 13` (quita los 2 últimos dígitos). También debe imprimirse sin ceros a la izquierda.

### El `.hpp`: diseño de la clase

```cpp
class bigint {
    private:
        std::string _val;
        void _trim();
    public:
        bigint();
        bigint(unsigned int n);
        bigint(std::string str);
        ...
};
```

La decisión de diseño clave es **guardar el número como `std::string`** (cada carácter es un dígito). Esto es lo que permite tener números arbitrariamente grandes: el tamaño del `string` no tiene el límite de un `int`.

Fíjate en los tres constructores: por defecto (`bigint()`), desde `unsigned int` (para poder escribir `bigint a(42);`) y desde `std::string` (útil internamente, para construir el resultado de operaciones ya como cadena).

También hay una idea interesante: los operadores `<<`/`>>` están duplicados, una versión que recibe `unsigned int` y otra que recibe `const bigint&` ("reuse" en el comentario del `.hpp`). Esto es porque el propio bigint puede necesitar desplazarse por una cantidad que a su vez es un `bigint` (ver el `main`: `d >>= (const bigint)2`).

### El `.cpp`: cómo funciona cada pieza

**`_trim()`** — quita ceros a la izquierda, salvo que el número sea "0" (deja al menos un dígito):
```cpp
void bigint::_trim() {
    size_t i = 0;
    while (i + 1 < _val.length() && _val[i] == '0') i++;
    _val = _val.substr(i);
}
```
Esto se llama cada vez que se construye un `bigint` desde un string, para garantizar la regla del enunciado: "sin ceros a la izquierda".

**Suma (`operator+`)** — es el algoritmo manual de "sumar en columna" que aprendiste en el colegio, pero recorriendo el string de derecha a izquierda:
```cpp
bigint bigint::operator+(const bigint& other) const {
    std::string res;
    int carry = 0, i = _val.length() - 1, j = other._val.length() - 1;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry + (i >= 0 ? _val[i--] - '0' : 0) + (j >= 0 ? other._val[j--] - '0' : 0);
        res += sum % 10 + '0'; carry = sum / 10;
    }
    std::reverse(res.begin(), res.end());
    return bigint(res);
}
```
- `i` y `j` empiezan en el último carácter de cada número (el dígito de las unidades).
- En cada vuelta se suman el dígito de `*this`, el de `other` y el acarreo (`carry`) del paso anterior.
- `sum % 10` es el dígito que se añade al resultado; `sum / 10` es el nuevo acarreo.
- Como se va construyendo de "unidades" hacia "más significativo", al final hay que invertir el string (`std::reverse`).
- El bucle sigue mientras queden dígitos en cualquiera de los dos números **o** quede acarreo pendiente (para el caso `99 + 1 = 100`).
- `_val[i] - '0'` es el truco habitual para convertir un carácter dígito (`'7'`) a su valor numérico (`7`), aprovechando que en la tabla ASCII los dígitos son consecutivos.

**Digitshift**:
```cpp
bigint bigint::operator<<(unsigned int n) const {
    return _val == "0" ? *this : bigint(_val + std::string(n, '0'));
}
bigint bigint::operator>>(unsigned int n) const {
    return n >= _val.length() ? bigint("0") : bigint(_val.substr(0, _val.length() - n));
}
```
- `<<` añade `n` ceros **al final** del string (multiplicar por 10ⁿ en base 10), salvo si el número ya es "0" (para no convertirlo en "000").
- `>>` recorta los últimos `n` caracteres del string (dividir por 10ⁿ), y si `n` es mayor o igual que la longitud del número, el resultado es directamente "0".
- `<<=` y `>>=` simplemente reasignan `*this` al resultado de `<<`/`>>` (mismo patrón "compuesto se define con el simple" que en `vect2`, aunque aquí al revés: primero se define el operador binario y el compuesto reutiliza).

**Versión "reuse" con `bigint` como argumento**:
```cpp
int bigint::toInt() const { return std::atoi(_val.c_str()); }
bigint bigint::operator<<(const bigint& other) const { return *this << other.toInt(); }
```
`toInt()` convierte el string a un `int` normal (usando `atoi`), y las sobrecargas que reciben `const bigint&` simplemente delegan en las versiones que reciben `unsigned int`, convirtiendo primero el argumento con `toInt()`.

**Comparaciones**:
```cpp
bool bigint::operator==(const bigint& other) const { return _val == other._val; }
bool bigint::operator<(const bigint& other) const {
    return _val.length() != other._val.length() ? _val.length() < other._val.length() : _val < other._val;
}
```
- `==` compara directamente los strings (funciona porque ya están sin ceros a la izquierda: "42" y "042" nunca coexistirían).
- `<` es el detalle más importante de todo el ejercicio: **no puedes comparar los strings directamente con `<`** cuando tienen distinta longitud, porque la comparación de `std::string` es lexicográfica (alfabética), y por ejemplo `"9" < "10"` sería `false` con comparación de strings normal (compara carácter a carácter: `'9' > '1'`), aunque numéricamente 9 < 10. Por eso primero se compara la **longitud** (un número con más dígitos siempre es mayor, asumiendo que no hay ceros a la izquierda) y solo si tienen la misma longitud se comparan los strings directamente (ahí sí, comparar carácter a carácter coincide con el orden numérico).
- El resto de comparaciones (`!=`, `>`, `<=`, `>=`) se derivan de `==` y `<`, tal como indica el comentario del `.hpp` ("the rest derives from those two"): por ejemplo `a > b` es lo mismo que `b < a`, y `a <= b` es lo mismo que "no (b < a)".

**Incremento**:
```cpp
bigint& bigint::operator++() { return *this += bigint(1); }
bigint bigint::operator++(int) { bigint tmp(*this); ++*this; return tmp; }
```
Mismo patrón pre/post que en `vect2`: el pre-incremento suma 1 usando la suma ya implementada, y el post-incremento guarda una copia antes de modificar.

**Impresión**:
```cpp
std::ostream& operator<<(std::ostream& os, const bigint& obj) { return os << obj.getVal(); }
```
Función libre (igual que en `vect2`) que usa `getVal()` para acceder al string privado desde fuera de la clase.

---

## 3. `polyset` — Herencia múltiple/virtual: de "bolsa" (`bag`) a "conjunto" (`set`)

Este es el ejercicio más conceptual de los tres: pone a prueba la **herencia múltiple con clases abstractas** y el **problema del diamante**.

### Las piezas que ya te dan (no hay que tocarlas)

- **`bag`** — clase abstracta pura (interfaz): declara `insert`, `print`, `clear` como `virtual ... = 0`. No se puede instanciar directamente.
- **`searchable_bag`** — hereda **virtualmente** de `bag` y añade `has(int) const = 0`. También es abstracta.
- **`array_bag`** — implementación concreta de `bag` usando un array dinámico de `int` (`insert`, `print`, `clear`, con gestión manual de memoria: constructor de copia, `operator=` y destructor que hacen `new[]`/`delete[]`).
- **`tree_bag`** — implementación concreta de `bag` usando un árbol binario de búsqueda (los `insert` van comparando valores para decidir si van a la izquierda o derecha del árbol; `destroy_tree`/`copy_node` son funciones recursivas auxiliares para el destructor y el constructor de copia).

Fíjate que tanto `array_bag` como `tree_bag` heredan de `bag` con `virtual public bag`. Esto es la clave de todo el ejercicio.

### ¿Por qué "herencia virtual"? El problema del diamante

Se pide crear `searchable_array_bag`, que debe heredar **a la vez** de `array_bag` (para tener el array y sus métodos) y de `searchable_bag` (para cumplir el contrato de `has()`). Pero `searchable_bag` **también** hereda de `bag`, igual que `array_bag`. Sin herencia virtual, `searchable_array_bag` acabaría con **dos copias independientes** de `bag` (una vía `array_bag`, otra vía `searchable_bag`), lo cual es ambiguo y rompe el polimorfismo (no sabrías cuál de las dos usar al convertir a `bag*`). Esto es el clásico **"problema del diamante"**:

```
        bag
       /   \
  array_bag  searchable_bag
       \   /
  searchable_array_bag
```

Al declarar `array_bag` y `searchable_bag` como `virtual public bag`, C++ garantiza que solo exista **una única subobjeto `bag`** compartido, sin importar por cuántos caminos se herede de él. Por eso en `bag.hpp`/`array_bag.hpp`/`searchable_bag.hpp` verás siempre `virtual public bag`.

### `searchable_array_bag` y `searchable_tree_bag`

```cpp
class searchable_array_bag : public array_bag, public searchable_bag {
    public:
        searchable_array_bag();
        searchable_array_bag(const searchable_array_bag& src);
        searchable_array_bag& operator=(const searchable_array_bag& other);
        ~searchable_array_bag();
        bool has(int value) const;
};
```

La clase hereda de las dos ramas del diamante y solo tiene que:
1. Implementar el único método que faltaba, `has()`, que en el caso del array es una búsqueda lineal:
```cpp
bool searchable_array_bag::has(int value) const {
    for (int i = 0; i < size; i++)
        if (data[i] == value) return true;
    return false;
}
```
   `size` y `data` son accesibles directamente porque son `protected` en `array_bag`.

2. Respetar la **forma canónica ortodoxa** (constructor por defecto, constructor de copia, `operator=`, destructor), delegando en la implementación de `array_bag` para no duplicar lógica de gestión de memoria:
```cpp
searchable_array_bag::searchable_array_bag(const searchable_array_bag& src) : array_bag(src) {}
```

`searchable_tree_bag` sigue exactamente la misma idea, pero `has()` aprovecha que el árbol es un **árbol binario de búsqueda** (BST) para hacer una búsqueda eficiente en lugar de lineal:
```cpp
bool searchable_tree_bag::has(int value) const {
    node* current = tree;
    while (current != NULL) {
        if (current->value == value) return true;
        else if (value < current->value) current = current->l;
        else current = current->r;
    }
    return false;
}
```
En cada paso descarta la mitad del árbol (va a la izquierda si el valor buscado es menor, a la derecha si es mayor), tal y como fue construido en `tree_bag::insert`.

### `set` — de bolsa a conjunto

La diferencia entre una **bolsa** (`bag`, permite duplicados) y un **conjunto** (`set`, no permite duplicados) es puramente de comportamiento en `insert`. En vez de reimplementar todo desde cero, `set` **envuelve** (usa composición, no herencia) una `searchable_bag` ya existente **por referencia**:

```cpp
class set {
    private:
        searchable_bag& _bag;
        set(); // prohibido: no tiene sentido un set sin bolsa
        set(const set& src); // prohibido: ver más abajo
        set& operator=(const set& other); // prohibido
    public:
        set(searchable_bag& other_s_bag);
        ...
};
```

Puntos importantes:
- `_bag` es una **referencia**, no un puntero ni una copia. Una referencia en C++ debe inicializarse obligatoriamente en la lista de inicialización del constructor (por eso `set::set(searchable_bag& other_s_bag) : _bag(other_s_bag) {}`) y **nunca puede volver a apuntar a otra cosa** una vez fijada.
- Precisamente por eso el constructor por defecto, el constructor de copia y el `operator=` se declaran **privados y sin implementación** (típico truco de C++98, antes de que existiera `= delete`): una referencia no se puede "reasignar", así que copiar o asignar un `set` no tendría sentido real, y se bloquea a propósito para que el compilador dé error si alguien lo intenta.
- La lógica de "ser un conjunto" está solo en `insert`:
```cpp
void set::insert(int value) {
    if (!this->has(value)) {
        _bag.insert(value);
    }
}
```
Antes de insertar, comprueba con `has()` (que delega en `_bag.has()`) si el valor ya existe; si existe, no hace nada. Así se garantiza que no haya duplicados, sin tener que reescribir ninguna estructura de datos: `set` es una capa fina de lógica encima de cualquier `searchable_bag` (ya sea de array o de árbol, ¡no le importa cuál!). Esto es un buen ejemplo del principio de **composición sobre herencia** y de **programar contra una interfaz** (`searchable_bag`) en vez de contra una implementación concreta.

### Cómo se conecta todo en el `main`

```cpp
searchable_bag *t = new searchable_tree_bag;
searchable_bag *a = new searchable_array_bag;
```
Aquí se ve el polimorfismo en acción: variables del tipo abstracto `searchable_bag*` apuntando a objetos concretos. Gracias a la herencia virtual, esto funciona sin ambigüedad.

```cpp
set sa(*a);
set st(*t);
```
Se crean conjuntos que "envuelven" esas bolsas ya existentes — `sa` filtra duplicados sobre el array, `st` filtra duplicados sobre el árbol, pero ambos comparten exactamente el mismo código de `set`.

---

## Resumen de ideas transversales del examen

| Concepto | Dónde aparece |
|---|---|
| Forma canónica ortodoxa (constructor, copia, `operator=`, destructor) | Los tres ejercicios |
| Definir operador compuesto en términos del simple (o viceversa) | `vect2` (`+=`→`+`), `bigint` (`<<`→`<<=`) |
| Pre vs. post incremento/decremento (firma con/sin `int`) | `vect2`, `bigint` |
| Operadores como funciones libres (`operator<<` para imprimir, `operator*` con escalar a la izquierda) | `vect2`, `bigint` |
| Derivar operadores de comparación a partir de `==` y `<` | `bigint` |
| Herencia virtual para resolver el problema del diamante | `polyset` |
| Composición mediante referencia + bloqueo de copia/asignación en C++98 | `set` |
| Uso de `protected` para compartir datos con clases derivadas | `array_bag`/`tree_bag` → `searchable_*` |

Si quieres, puedo generar también una versión con ejercicios de autoevaluación (preguntas tipo "qué imprime esta línea") para practicar antes del examen real.
