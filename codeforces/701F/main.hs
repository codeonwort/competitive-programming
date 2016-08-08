import qualified Data.Map.Strict as Map
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8
import Control.Monad
import Data.Maybe
import Debug.Trace

getInt = read `fmap` getLine :: IO Int
getInts = (map (fst . fromJust . BS8.readInt) . BS8.words) `fmap` BS.getLine :: IO [Int]

type Graph = Map.Map (Int,Int) [Int]
type Link = Map.Map Int [Int]
type Visited = Map.Map Int Bool
type Path = [(Int,Int)]

main = do
	[n,m] <- getInts -- num of vertices, edges
	[s,t] <- getInts -- starting vertex, terminal vertex
	edges <- replicateM m getInts
	let g = foldl addEdge Map.empty edges
	let links = foldl addLink Map.empty edges
	case findPath g links s t of
		Nothing -> print (-1)
		Just path -> case bridges g links path of
			[] -> print path >> print (-1)
			br -> print path >> print br {-do
				let soln1 = solve1
				let soln2 = solve2
				if soln2 == [] || cost soln1 < cost soln2
				then printSoln soln1
				else printSoln soln2-}

addEdge :: Graph -> [Int] -> Graph
addEdge g [u,v,w] = Map.insertWith (++) (u',v') [w] g where
	u' = if u > v then v else u
	v' = if u > v then u else v

addLink :: Link -> [Int] -> Link
addLink links [u,v,w] = Map.insertWith (++) v [u] (Map.insertWith (++) u [v] links)

findPath :: Graph -> Link -> Int -> Int -> Maybe Path
findPath g links s t = case f s Map.empty of
	[] -> Nothing
	solns -> Just (head solns)
	where f x visited = do
		y <- links Map.! x -- vertices connected with x
		guard (y `Map.notMember` visited)
		if y == t
		then return [(x,y)]
		else f y (Map.insert y True visited) >>= \soln -> return $ (x,y):soln

postorder :: Tree -> Int -> [(Int,Int)] -- [(curr,prev)]
postorder tree start = f Set.empty 0 start where
	f visited prev curr
		| vs == [] = [(curr,prev)]
		| otherwise = concat (map (f visited' curr) vs) ++ [(curr,prev)]
		where
			visited' = Set.insert curr visited
			vs = filter (`Set.notMember` visited') (snd $ tree Map.! curr)

bridges :: Graph -> Link -> Path -> [(Int,Int)]
bridges g links path = dfs Map.empty [] start where
	start = fst (head path)
	dfs visited br curr
		| ys == [] = trace (show (curr, links Map.! curr)) br
		| otherwise = trace (show curr) $ foldl (dfs visited') br' ys
		where
			ys = filter (\y -> y `Map.notMember` visited) (links Map.! curr)
			visited' = Map.insert curr True visited
			br' = foldl (checkBridge curr) br ys
			sole x = length (links Map.! curr) == 1
			checkBridge curr br next
				| sole curr && sole next = (curr,next):br
				| otherwise = br

{-
bridges g links path = concat $ f start Map.empty where
	start = fst (head path)
	f x visited = do
		y <- links Map.! x
		guard (y `Map.notMember` visited)
		let x_ok = length (links Map.! x) == 1
		let y_ok = length (links Map.! y) == 1
		let visited' = Map.insert x True visited
		if x_ok && y_ok
		then return [(x,y)]
		else f y visited' >>= \brs -> return $ (x,y):brs
-}
{-
bridges :: Graph -> Path -> [(Int,Int)]
bridges g path = filter (\e -> e `elem` path) edges where
	edges :: [(Int,Int)]
	edges = filter (\e -> length (g Map.! e) == 1) (Map.keys g)
-}
