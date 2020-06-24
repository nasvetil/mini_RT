#include "doom.h"

// Ф-ия определяла, пересекает ли луч объект (шар)
// ->
// Ф-ия возвращает точку попадания
double		hit_sphere(t_vector3 center, t_vector3 orig, t_vector3 dir, float radius)
{
	t_vector3	oc;
	float		desc;
	float		a;
	float		b;
	float		c;

	oc = ft_vec3_sub(&orig, &center);
	a = ft_vec3_dot_product(&dir, &dir);
	b = 2.0 * ft_vec3_dot_product(&oc, &dir);
	c = ft_vec3_dot_product(&oc, &oc) - radius * radius;
	desc = b * b - 4 * a * c;

	// Возвращает -1, если луч не проходит через круг
	if (desc < 0)
		return (-1.0);
	else
		return (-b - sqrt(desc)) / (2.0 * a);
}

// Определяет цвет каждого пикселю по лучу
t_vector3	ft_color(t_vector3 dir)
{
	t_vector3	unit_dir;
	float		t;
	t_vector3	vec_1;
	t_vector3	vec_05;
	t_vector3	vec_12;
	t_vector3	vec_052;

	t_vector3	vec_light = (t_vector3){1.0, 1.0, 1.0, 0.0}; // Некоторый точечный источник света
	t_vector3	normal_vec_light = ft_vec3_normalize(&vec_light);

	t_vector3	color_vec = (t_vector3){1.0, 0.0, 0.0, 0.0}; // red

	t = hit_sphere((t_vector3){0.0, 0.0, -1.0, 0.0}, (t_vector3){0.0, 0.0, 0.0, 0.0}, dir, 0.5);

	// Если hit_sphere вернёт true, то область занята некоторым объектом
	if (t > 0.0)
	{
		// Temp add: добавляем степень освещённости объекта
		// Чем больше угол между источником света и нормали в точке пересечения, тем ярче цвет объекта

		// 1. Вычислим ненормализованный вектор
		t_vector3 v = ft_vec3_add(ft_vec3_add(
			(t_vector3){0.0, 0.0, 0.0, 0.0}, // orig
			ft_vec3_scalar_product(&dir, t) // dir * t
		), (t_vector3){0.0, 0.0, -1.0, 0.0});

		// 2. Вычислим нормализованный вектор
		t_vector3 n = ft_vec3_normalize(&v);
		// return ((t_vector3){(n.x + 1), (n.y + 1), (n.z + 1), 0.0}); // Выведет деление на сектора (неожиданно)

		// 3. Рассчитаем угол между источником света и объектом
		// Скалярное произведение нормированных векторов = cos угла между ними
		double intensive = ft_vec3_dot_product(&n, &normal_vec_light);

		return (ft_vec3_scalar_product(&color_vec, intensive));
	}

	// Далее -- расчёт фонового градиента
	vec_1 = (t_vector3){1.0, 1.0, 1.0, 0.0};
	vec_05 = (t_vector3){0.5, 0.7, 1.0, 0.0};
	unit_dir = ft_vec3_normalize(&dir);

	// Используется непосредственно для создания градиента
	// (отвечает за насыщенность цвета)
	t = 0.5 * (unit_dir.y + 1.0);

	vec_12 = ft_vec3_scalar_product(&vec_1, (1.0 - t));
	vec_052 = ft_vec3_scalar_product(&vec_05, t);

	return ((t_vector3)ft_vec3_add(vec_12, vec_052));
}

void		ft_render_redraw(t_wolf3d *w, t_list *dom)
{
	(void)dom;

	// Счётчики
	float x;
	float y;
	int wid = 0;

	// Коэффициенты отклонения луча
	float u;
	float v;

	// Вектор цвета (буфер для каждого луча)
	t_vector3 col;

	// Свойства сцены
	t_vector3 *orig;
	t_vector3 *left_corner;
	t_vector3 *horizontal;
	t_vector3 *vertical;


	orig = ft_my_malloc(sizeof(t_vector3));
	left_corner = ft_my_malloc(sizeof(t_vector3));
	horizontal = ft_my_malloc(sizeof(t_vector3));
	vertical = ft_my_malloc(sizeof(t_vector3));

	// orig пока нигде не используется
	*orig = (t_vector3){0.0, 0.0, 0.0, 0.0};

	// left_corner -- настройки камеры (расположение камеры?)
	/* left_corner = (t_vector3){смещение по горизонтали, смещение по вертикали, ~zoom, 0} */
	*left_corner = (t_vector3){-16.0, -9.0, -9.0, 0.0};

	// horizontal, vertical -- отвечают за пропорцию проекции
	// (за угол обзора fov)
	*horizontal = (t_vector3){32.0, 0.0, 0.0, 0.0};
	*vertical = (t_vector3){0.0, 18.0, 0.0, 0.0};

	x = 0;
	y = WIN_HEIGHT - 1;
	wid = 0;

	while (y >= 0 && wid < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			// Коэффициенты отклонения луча
			u = (float)(x / WIN_WIDTH);
			v = (float)(y / WIN_HEIGHT);

			// Цвет выражен через вектор
			col = ft_color(ft_vec3_add(ft_vec3_add(*left_corner, \
				ft_vec3_scalar_product(horizontal, u)), ft_vec3_scalar_product(vertical, v)));
			// col = (t_vector3){x / WIN_WIDTH, y / WIN_HEIGHT, 0.2, 0.0};
			int ir = (255.99 * col.x);
			int ig = (255.99 * col.y);
			int ib = (255.99 * col.z);
			w->sdl->pixels[(int)wid*WIN_WIDTH + (int)x] = ft_rgb_to_hex(ir,ig,ib);
			x++;
		}
		wid++;
		y--;
	}
}