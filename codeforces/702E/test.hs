import Control.Monad

n = 100000
k = 10000000000

main = do
	putStrLn "100000 10000000000"
	forM [0..n-1] $ \i -> do
		putStr (show i)
		putChar ' '
	putChar '\n'
	forM [0..n-1] $ \i -> do
		putChar '1'
		putChar ' '
