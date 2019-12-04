// http://codeforces.com/problemset/problem/687/A

use std::io::stdin;

fn read_ints() -> Vec<i32> {
	let mut s = String::new();
	stdin().read_line(&mut s).unwrap();
	
	let mut v: Vec<i32> = Vec::new();
	for w in s.trim().split(" ") {
		let x: i32 = w.parse().unwrap();
		v.push(x);
	}

	return v;
}

fn main() {
	let nm = read_ints();
	let n = nm[0]; // num vertices
	let m = nm[1]; // num edges

	let mut edges: Vec<Vec<i32>> = Vec::new();
	edges.resize(n as usize, Vec::new());
	
	for _ in 0..m {
		let uv = read_ints();
		let u = uv[0] - 1;
		let v = uv[1] - 1;
		edges[u as usize].push(v);
		edges[v as usize].push(u);
	}

	// 0: unvisited, 1:black, 2:white
	let mut colors: Vec<i32> = Vec::new();
	colors.resize(n as usize, 0);

	// Oops... running dfs only once on a non-isolated vertex fails
	// if the input contains multiple non-degenerate graphs!
	for i in 0..n {
		if colors[i as usize] == 0 {
			dfs(&mut colors, &edges, i, 1);
		}
	}

	let mut set_a: Vec<i32> = Vec::new();
	let mut set_b: Vec<i32> = Vec::new();
	for i in 0..n {
		if colors[i as usize] == 1 {
			set_a.push(i);
		} else if colors[i as usize] == 2 {
			set_b.push(i);
		}
	}

	// Print solution
	if is_vertex_cover(&set_a, &edges) && is_vertex_cover(&set_b, &edges) {
		println!("{}", set_a.len());
		for v in set_a {
			print!("{} ", v + 1);
		}
		println!("");
		println!("{}", set_b.len());
		for v in set_b {
			print!("{} ", v + 1);
		}
		println!("");

	} else {
		println!("-1");
	}
}

fn dfs(colors: &mut Vec<i32>, edges: &Vec<Vec<i32>>, vertex: i32, vertex_color: i32) {
	colors[vertex as usize] = vertex_color;
	for i in 0..edges[vertex as usize].len() {
		let neighbor = edges[vertex as usize][i];
		if colors[neighbor as usize] == 0 {
			dfs(colors, edges, neighbor, if vertex_color == 1 { 2 } else { 1 });
		}
	}
}

use std::collections::HashSet;
fn is_vertex_cover(vs: &Vec<i32>, edges: &Vec<Vec<i32>>) -> bool {
	let mut vertices: HashSet<i32> = HashSet::new();
	for v in vs {
		vertices.insert(*v);
	}
	let n = edges.len();
	for u in 0..n {
		let m = edges[u].len();
		for v_ix in 0..m {
			let v = edges[u][v_ix];
			if !vertices.contains(&(u as i32)) && !vertices.contains(&(v as i32)) {
				return false;
			}
		}
	}
	return true;
}

