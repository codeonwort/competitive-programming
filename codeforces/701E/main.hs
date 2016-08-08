import Control.Monad
import Data.Array
import Data.Maybe
import qualified Data.Map.Strict as Map
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8

getInt = read `fmap` getLine :: IO Int
--getInts = (map read . words) `fmap` getLine :: IO [Int]
getInts = (map (fst . fromJust . BS8.readInt) . BS8.words) `fmap` BS.getLine :: IO [Int]

type Tree = Map.Map Int (Int, [Int]) -- (data, children)

main = do
	[n, k] <- getInts
	cities <- getInts
	edges <- replicateM (n-1) getInts
	let tree0 = Map.fromList [(key, (0,[])) | key <- [1..n]] :: Tree
	let tree = foldl addCity (foldl addEdge tree0 edges) cities
	let t = dfs tree 1
	print $ answer t n (k*2)

addEdge :: Tree -> [Int] -> Tree
addEdge g [u,v] = g'' where
	g' = Map.update (\(x,es) -> Just (x,u:es)) v g
	g'' = Map.update (\(x,es) -> Just (x,v:es)) u g'

addCity :: Tree -> Int -> Tree
addCity g i = Map.update (\(_,es) -> Just (1,es)) i g

dfs :: Tree -> Int -> Tree
dfs tree start = f 0 tree start where
	link curr prev = filter (/= prev) $ snd (tree Map.! curr)
	f prev tree curr
		| snd (tree Map.! curr) == [] = tree
		| otherwise = let x = foldl (f curr) tree (link curr prev) in seq x (calc x curr prev)
	calc tree curr prev = Map.update (\(d,es) -> Just (d+cost,es)) curr tree where
		cost = sum $ map (\j -> fst (tree Map.! j)) (link curr prev) :: Int

answer :: Tree -> Int -> Int -> Integer
answer tree n k2 = sum $ map (\i -> min (cnt i) (k2' - (cnt i))) [1..n] where
	k2' = fromIntegral k2
	cnt i = fromIntegral $ fst (tree Map.! i)

